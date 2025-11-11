# Disable the "factory" merge so no integer addresses ever hit join().
Import("env")
env.Replace(FLASH_EXTRA_IMAGES=[])

# Simplest version: copy all .bin files from build env to where ESPHome looks
Import("env")
import os, shutil, glob

# TODO: frankly, i'm not sure if this portion of the file is still doing anything?
print(f"Executing binary file movement fix and setting FLASH_EXTRA_IMAGES to empty list")
proj = env.subst("$PROJECT_DIR")
bdir = env.subst("$BUILD_DIR")

# TODO: i think basically this would get the right files but im 
# not running it at the correct point post build and pre-compile where it would move things in time
binfiles = [os.path.relpath(file, bdir) for file in glob.glob(os.path.join(bdir, "*.bin"))]
if binfiles == []:
    print("There are no binary files to move at this time from build directory: {bdir}")

print(binfiles)
for name in binfiles:
    print(name)
    src = os.path.join(bdir, name)
    dst = os.path.join(proj, name)
    if os.path.exists(src):
        shutil.copy2(src, dst)
        print(f"simple_factory_fix: staged {name}")
    else:
        print("generated a bad file")