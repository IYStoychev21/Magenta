import subprocess

subprocess.run("start vendor/premake/premake5.exe gmake", shell=True)
subprocess.run("make", shell=True)
subprocess.run("start bin/Debug-windows-x86_64/SandBox/Sandbox.exe", shell=True)
