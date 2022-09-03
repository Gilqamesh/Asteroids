set CommonCompilerFlags=-Oi -O2 -FC -Zi -nologo -EHa -MD -DG_DEBUG=1
set CommonLinkerFlags=-incremental:no -opt:ref -subsystem:WINDOWS raylib.lib Kernel32.lib user32.lib opengl32.lib gdi32.lib winmm.lib Shell32.lib
echo WAITING FOR PDB > lock.tmp
cl %CommonCompilerFlags% /Fe: GameLayer.dll src/GameLayer.cpp -LD /link %CommonLinkerFlags% -EXPORT:UpdateAndRender -EXPORT:LoadResources -EXPORT:SetupWindows
del lock.tmp
cl %CommonCompilerFlags% /Fe: asteroids src/win32_asteroids.cpp /link %CommonLinkerFlags%
