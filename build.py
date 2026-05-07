import os
import re
import subprocess
import platform

# 用來抓取 C++ 函數的正規表達式
FUNC_PATTERN = re.compile(r'^([a-zA-Z_][a-zA-Z0-9_:\s\*&]+)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\((.*?)\)\s*\{')

def generate_headers(cpp_files):
    for cpp_file in cpp_files:
        if "main.cpp" in cpp_file:
            continue
            
        header_file = cpp_file.replace('.cpp', '.h')
        header_name = os.path.basename(header_file).replace('.', '_').upper()
        
        # FIX: 如果名稱開頭是數字，C++ 會報錯，所以加上前綴
        if header_name[0].isdigit():
            header_name = "HEADER_" + header_name
        
        functions = []
        with open(cpp_file, 'r', encoding='utf-8') as f:
            for line in f:
                match = FUNC_PATTERN.match(line)
                if match:
                    ret_type, func_name, args = match.groups()
                    if func_name != 'main' and 'if' not in ret_type and 'while' not in ret_type:
                        functions.append(f"{ret_type.strip()} {func_name.strip()}({args});")
        
        with open(header_file, 'w', encoding='utf-8') as f:
            f.write(f"#ifndef {header_name}\n")
            f.write(f"#define {header_name}\n\n")
            f.write("// Auto-generated Header\n")
            for func in functions:
                f.write(func + "\n")
            f.write(f"\n#endif // {header_name}\n")
            
        print(f"[Success] Generated header: {header_file}")

def compile_project(cpp_files):
    is_windows = platform.system() == "Windows"
    output_win = "UltimateProject.exe"
    output_linux = "UltimateProject.out"
    
    cmd_win = ["g++"] + cpp_files + ["-o", output_win]
    cmd_linux = ["g++"] + cpp_files + ["-o", output_linux]
    
    print("\n--- Compiling ---")
    
    try:
        if is_windows:
            subprocess.run(cmd_win, check=True)
            print(f"[Build Success] Executable created: {output_win}")
        else:
            subprocess.run(cmd_linux, check=True)
            print(f"[Build Success] Executable created: {output_linux}")
    except subprocess.CalledProcessError:
        print("[Error] Build failed! Please check your C++ syntax.")

if __name__ == "__main__":
    cpp_files = []
    for root, dirs, files in os.walk("."):
        for file in files:
            if file.endswith(".cpp"):
                path = os.path.join(root, file).replace('\\', '/')
                cpp_files.append(path)
                
    if not cpp_files:
        print("No .cpp files found!")
    else:
        generate_headers(cpp_files)
        compile_project(cpp_files)