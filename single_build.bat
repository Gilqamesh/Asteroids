set CommonCompilerFlags=-Oi -O2 -nologo -EHa -MD
set CommonLinkerFlags=static_raylib.lib Kernel32.lib user32.lib opengl32.lib gdi32.lib winmm.lib Shell32.lib
cl %CommonCompilerFlags% /Fe: asteroids -DSINGLE_FILE_BUILD src/win32_asteroids.cpp %CommonLinkerFlags%
