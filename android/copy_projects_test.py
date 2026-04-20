import os
import shutil
import re

source_path = r"g:\Workspaces\cpp\LearnOpenGL\android\1.getting_started\1.1.hello_window"
log_path = r"g:\Workspaces\cpp\LearnOpenGL\android\copy_log_test.txt"

# Test with just a few modules
modules = [
    ":1.getting_started:2.4.hello_triangle_exercise2",
    ":1.getting_started:2.5.hello_triangle_exercise3",
    ":2.lighting:1.colors"
]

def clean_name(s):
    result = re.sub(r'\d+\.', '', s)
    result = result.lstrip('.')
    result = result.rstrip('.')
    return result

def clean_package_name(s):
    result = clean_name(s)
    result = result.replace(':', '_')
    return result

def clean_path_name(s):
    result = s.replace(':', '_')
    return result

def log(message):
    print(message)
    with open(log_path, 'a', encoding='utf-8') as f:
        f.write(message + '\n')

# Clear log file
if os.path.exists(log_path):
    os.remove(log_path)

log("Starting script...")
log(f"Source path: {source_path}")
log(f"Source path exists: {os.path.exists(source_path)}")
log(f"Modules count: {len(modules)}")

# Get items to copy (excluding build directories)
items_to_copy = []
if os.path.exists(source_path):
    for item in os.listdir(source_path):
        if item not in ['.cxx', 'build', '.gradle']:
            items_to_copy.append(item)
    log(f"Items to copy: {items_to_copy}")

for idx, module in enumerate(modules, 1):
    log(f"\nProcessing module {idx}/{len(modules)}: {module}")
    
    try:
        module_trimmed = module.lstrip(':')
        last_colon_index = module_trimmed.rfind(':')
        title_name = module_trimmed[:last_colon_index]
        tutorial_name = module_trimmed[last_colon_index+1:]
        
        title_name_clean = clean_package_name(title_name)
        tutorial_name_clean = clean_name(tutorial_name)
        
        # Clean title name for path (replace colons)
        title_name_path = clean_path_name(title_name)
        
        target_path = os.path.join(r"g:\Workspaces\cpp\LearnOpenGL\android", title_name_path, tutorial_name)
        
        log(f"  Target: {target_path}")
        log(f"  ApplicationId: com.example.learnopengl.{title_name_clean}.{tutorial_name_clean}")
        
        # Create directory if it doesn't exist
        if not os.path.exists(target_path):
            os.makedirs(target_path, exist_ok=True)
            log("  Created directory")
        
        # Copy files
        log("  Starting copy...")
        for item in items_to_copy:
            s = os.path.join(source_path, item)
            d = os.path.join(target_path, item)
            log(f"    Copying: {item}")
            if os.path.isdir(s):
                if os.path.exists(d):
                    shutil.rmtree(d)
                shutil.copytree(s, d)
                log(f"    Copied dir: {item}")
            else:
                if os.path.exists(d):
                    os.remove(d)
                shutil.copy2(s, d)
                log(f"    Copied file: {item}")
        log("  Copied files successfully")
        
        # Update build.gradle.kts
        build_gradle_path = os.path.join(target_path, "build.gradle.kts")
        with open(build_gradle_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = re.sub(r'applicationId = "com\.example\.learnopengl\.[^"]+"', 
                        f'applicationId = "com.example.learnopengl.{title_name_clean}.{tutorial_name_clean}"', 
                        content)
        with open(build_gradle_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated build.gradle.kts")
        
        # Update CMakeLists.txt
        cmake_lists_path = os.path.join(target_path, "src/main/cpp/CMakeLists.txt")
        with open(cmake_lists_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = content.replace('project("hello_window")', f'project("{tutorial_name_clean}")')
        content = re.sub(r'set\(LEARN_OPENGL_TITLE "[^"]+"\)', f'set(LEARN_OPENGL_TITLE "{title_name}")', content)
        content = re.sub(r'set\(LEARN_OPENGL_TUTORIAL "[^"]+"\)', f'set(LEARN_OPENGL_TUTORIAL "{tutorial_name}")', content)
        content = content.replace('add_library(hello_window', f'add_library({tutorial_name_clean}')
        content = content.replace('target_link_libraries(hello_window', f'target_link_libraries({tutorial_name_clean}')
        with open(cmake_lists_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated CMakeLists.txt")
        
        # Update MyGLRenderer.kt
        renderer_path = os.path.join(target_path, "src/main/java/com/example/learnopengl/MyGLRenderer.kt")
        with open(renderer_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = content.replace('System.loadLibrary("hello_window")', f'System.loadLibrary("{tutorial_name_clean}")')
        with open(renderer_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated MyGLRenderer.kt")
        
        # Update strings.xml
        strings_path = os.path.join(target_path, "src/main/res/values/strings.xml")
        with open(strings_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = re.sub(r'<string name="app_name">[^<]+</string>', f'<string name="app_name">{tutorial_name}</string>', content)
        with open(strings_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated strings.xml")
        
        log("  Done!")
    except Exception as e:
        import traceback
        log(f"  ERROR: {str(e)}")
        log(f"  Traceback: {traceback.format_exc()}")
        log("  Continuing with next module...")

log("\nAll modules processed successfully!")