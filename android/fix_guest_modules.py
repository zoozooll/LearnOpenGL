import os
import shutil

log_path = r"g:\Workspaces\cpp\LearnOpenGL\android\fix_guest_log.txt"

# List of guest modules with their correct paths
guest_modules = [
    ":8.guest:2020:oit",
    ":8.guest:2020:skeletal_animation",
    ":8.guest:2021:1.scene:1.scene_graph",
    ":8.guest:2021:1.scene:2.frustum_culling",
    ":8.guest:2021:2.csm",
    ":8.guest:2021:3.tessellation:terrain_gpu_dist",
    ":8.guest:2021:3.tessellation:terrain_cpu_src",
    ":8.guest:2021:4.dsa",
    ":8.guest:2022:5.computeshader_helloworld",
    ":8.guest:2022:6.physically_based_bloom",
    ":8.guest:2022:7.area_lights:1.area_light",
    ":8.guest:2022:7.area_lights:2.multiple_area_lights"
]

def log(message):
    print(message)
    with open(log_path, 'a', encoding='utf-8') as f:
        f.write(message + '\n')

# Clear log file
if os.path.exists(log_path):
    os.remove(log_path)

log("Starting to fix guest module paths...")

for module in guest_modules:
    # Remove leading colon and split by colons
    module_trimmed = module.lstrip(':')
    path_parts = module_trimmed.split(':')
    
    # Build the correct target path
    target_path = os.path.join(r"g:\Workspaces\cpp\LearnOpenGL\android", *path_parts)
    
    # The old path was created by replacing colons with underscores in the title part
    # For example: 8.guest:2021:1.scene became 8_guest_2021_1_scene
    old_title_part = path_parts[0]
    for part in path_parts[1:-1]:
        old_title_part += '_' + part
    
    # Old path format: android/old_title_part/tutorial_name
    old_path = os.path.join(r"g:\Workspaces\cpp\LearnOpenGL\android", old_title_part, path_parts[-1])
    
    log(f"\nProcessing: {module}")
    log(f"  Old path: {old_path}")
    log(f"  New path: {target_path}")
    
    # Check if old path exists
    if os.path.exists(old_path):
        # Create target directory if it doesn't exist
        if not os.path.exists(target_path):
            os.makedirs(os.path.dirname(target_path), exist_ok=True)
            log("  Created parent directories")
        
        # Move the directory
        try:
            shutil.move(old_path, target_path)
            log("  Moved successfully!")
        except Exception as e:
            log(f"  ERROR moving: {str(e)}")
    else:
        # Check if it already exists at the new path
        if os.path.exists(target_path):
            log("  Already exists at target path")
        else:
            log("  WARNING: Module not found at old or new path")

log("\nFinished processing guest modules!")