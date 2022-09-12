#include "platform.hpp"
#include "raylib.h"
#include "rlgl.h"

#if defined(SINGLE_FILE_BUILD)
#else
extern "C"
{
#endif

/***
 * CORE
 */
// Window-related functions
void RL_InitWindow(i32 width, i32 height, const char *title) // Initialize window and OpenGL context
{
    InitWindow(width, height, title);
}
b32 RL_WindowShouldClose(void) // Check if KEY_ESCAPE pressed or Close icon pressed
{
    return (WindowShouldClose());
}
void RL_CloseWindow(void) // Close window and unload OpenGL context
{
    CloseWindow();
}
b32 RL_IsWindowReady(void) // Check if window has been initialized successfully
{
    return (IsWindowReady());
}
b32 RL_IsWindowFullscreen(void) // Check if window is currently fullscreen
{
    return (IsWindowFullscreen());
}
b32 RL_IsWindowHidden(void) // Check if window is currently hidden (only PLATFORM_DESKTOP)
{
    return (IsWindowHidden());
}
b32 RL_IsWindowMinimized(void) // Check if window is currently minimized (only PLATFORM_DESKTOP)
{
    return (IsWindowMinimized());
}
b32 RL_IsWindowMaximized(void) // Check if window is currently maximized (only PLATFORM_DESKTOP)
{
    return (IsWindowMaximized());
}
b32 RL_IsWindowFocused(void) // Check if window is currently focused (only PLATFORM_DESKTOP)
{
    return (IsWindowFocused());
}
b32 RL_IsWindowResized(void) // Check if window has been resized last frame
{
    return (IsWindowResized());
}
b32 RL_IsWindowState(u32 flag) // Check if one specific window flag is enabled
{
    return (IsWindowState(flag));
}
void RL_SetWindowState(u32 flags) // Set window configuration state using flags (only PLATFORM_DESKTOP)
{
    SetWindowState(flags);
}
void RL_ClearWindowState(u32 flags) // Clear window configuration state flags
{
    ClearWindowState(flags);
}
void RL_ToggleFullscreen(void) // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
{
    ToggleFullscreen();
}
void RL_MaximizeWindow(void) // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
{
    MaximizeWindow();
}
void RL_MinimizeWindow(void) // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
{
    MinimizeWindow();
}
void RL_RestoreWindow(void) // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
{
    RestoreWindow();
}
void RL_SetWindowIcon(Image image) // Set icon for window (only PLATFORM_DESKTOP)
{
    SetWindowIcon(image);
}
void RL_SetWindowTitle(const char *title) // Set title for window (only PLATFORM_DESKTOP)
{
    SetWindowTitle(title);
}
void RL_SetWindowPosition(i32 x, i32 y) // Set window position on screen (only PLATFORM_DESKTOP)
{
    SetWindowPosition(x, y);
}
void RL_SetWindowMonitor(i32 monitor) // Set monitor for the current window (fullscreen mode)
{
    SetWindowMonitor(monitor);
}
void RL_SetWindowMinSize(i32 width, i32 height) // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
{
    SetWindowMinSize(width, height);
}
void RL_SetWindowSize(i32 width, i32 height) // Set window dimensions
{
    SetWindowSize(width, height);
}
void RL_SetWindowOpacity(r32 opacity) // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
{
    SetWindowOpacity(opacity);
}
void *RL_GetWindowHandle(void) // Get native window handle
{
    return (GetWindowHandle());
}
i32 RL_GetScreenWidth(void) // Get current screen width
{
    return (GetScreenWidth());
}
i32 RL_GetScreenHeight(void) // Get current screen height
{
    return (GetScreenHeight());
}
i32 RL_GetRenderWidth(void) // Get current render width (it considers HiDPI)
{
    return (GetRenderWidth());
}
i32 RL_GetRenderHeight(void) // Get current render height (it considers HiDPI)
{
    return (GetRenderHeight());
}
i32 RL_GetMonitorCount(void) // Get number of connected monitors
{
    return (GetMonitorCount());
}
i32 RL_GetCurrentMonitor(void) // Get current connected monitor
{
    return (GetCurrentMonitor());
}
Vector2 RL_GetMonitorPosition(i32 monitor) // Get specified monitor position
{
    return (GetMonitorPosition(monitor));
}
i32 RL_GetMonitorWidth(i32 monitor) // Get specified monitor width (current video mode used by monitor)
{
    return (GetMonitorWidth(monitor));
}
i32 RL_GetMonitorHeight(i32 monitor) // Get specified monitor height (current video mode used by monitor)
{
    return (GetMonitorHeight(monitor));
}
i32 RL_GetMonitorPhysicalWidth(i32 monitor) // Get specified monitor physical width in millimetres
{
    return (GetMonitorPhysicalWidth(monitor));
}
i32 RL_GetMonitorPhysicalHeight(i32 monitor) // Get specified monitor physical height in millimetres
{
    return (GetMonitorPhysicalHeight(monitor));
}
i32 RL_GetMonitorRefreshRate(i32 monitor) // Get specified monitor refresh rate
{
    return (GetMonitorRefreshRate(monitor));
}
Vector2 RL_GetWindowPosition(void) // Get window position XY on monitor
{
    return (GetWindowPosition());
}
Vector2 RL_GetWindowScaleDPI(void) // Get window scale DPI factor
{
    return (GetWindowScaleDPI());
}
const char *RL_GetMonitorName(i32 monitor) // Get the human-readable, UTF-8 encoded name of the primary monitor
{
    return (GetMonitorName(monitor));
}
void RL_SetClipboardText(const char *text) // Set clipboard text content
{
    SetClipboardText(text);
}
const char *RL_GetClipboardText(void) // Get clipboard text content
{
    return (GetClipboardText());
}
void RL_EnableEventWaiting(void) // Enable waiting for events on EndDrawing(), no automatic event polling
{
    EnableEventWaiting();
}
void RL_DisableEventWaiting(void) // Disable waiting for events on EndDrawing(), automatic events polling
{
    DisableEventWaiting();
}

// Custom frame control functions
// NOTE: Those functions are intended for advance users that want full control over the frame processing
// By default EndDrawing() does this job: draws everything + SwapScreenBuffer() + manage frame timming + PollInputEvents()
// To avoid that behaviour and control frame processes manually, enable in config.h: SUPPORT_CUSTOM_FRAME_CONTROL
void RL_SwapScreenBuffer(void) // Swap back buffer with front buffer (screen drawing)
{
    SwapScreenBuffer();
}
void RL_PollInputEvents(void) // Register all input events
{
    PollInputEvents();
}
void RL_WaitTime(r64 seconds) // Wait for some time (halt program execution)
{
    WaitTime(seconds);
}

// Cursor-related functions
void RL_ShowCursor(void) // Shows cursor
{
    ShowCursor();
}
void RL_HideCursor(void) // Hides cursor
{
    HideCursor();
}
b32 RL_IsCursorHidden(void) // Check if cursor is not visible
{
    return (IsCursorHidden());
}
void RL_EnableCursor(void) // Enables cursor (unlock cursor)
{
    EnableCursor();
}
void RL_DisableCursor(void) // Disables cursor (lock cursor)
{
    DisableCursor();
}
b32 RL_IsCursorOnScreen(void) // Check if cursor is on the screen
{
    return (IsCursorOnScreen());
}

// Drawing-related functions
void RL_ClearBackground(Color color) // Set background color (framebuffer clear color)
{
    ClearBackground(color);
}
void RL_BeginDrawing() // Setup canvas (framebuffer) to start drawing
{
    BeginDrawing();
}
void RL_EndDrawing(void) // End canvas drawing and swap buffers (r64 buffering)
{
    EndDrawing();
}
void RL_BeginMode2D(Camera2D camera) // Begin 2D mode with custom camera (2D)
{
    BeginMode2D(camera);
}
void RL_EndMode2D(void) // Ends 2D mode with custom camera
{
    EndMode2D();
}
void RL_BeginMode3D(Camera3D camera) // Begin 3D mode with custom camera (3D)
{
    BeginMode3D(camera);
}
void RL_EndMode3D(void) // Ends 3D mode and returns to default 2D orthographic mode
{
    EndMode3D();
}
void RL_BeginTextureMode(RenderTexture2D target) // Begin drawing to render texture
{
    BeginTextureMode(target);
}
void RL_EndTextureMode(void) // Ends drawing to render texture
{
    EndTextureMode();
}
void RL_BeginShaderMode(Shader shader) // Begin custom shader drawing
{
    BeginShaderMode(shader);
}
void RL_EndShaderMode(void) // End custom shader drawing (use default shader)
{
    EndShaderMode();
}
void RL_BeginBlendMode(i32 mode) // Begin blending mode (alpha, additive, multiplied, subtract, custom)
{
    BeginBlendMode(mode);
}
void RL_EndBlendMode(void) // End blending mode (reset to default: alpha blending)
{
    EndBlendMode();
}
void RL_BeginScissorMode(i32 x, i32 y, i32 width, i32 height) // Begin scissor mode (define screen area for following drawing)
{
    BeginScissorMode(x, y, width, height);
}
void RL_EndScissorMode(void) // End scissor mode
{
    EndScissorMode();
}

// Shader management functions
// NOTE: Shader functionality is not available on OpenGL 1.1
Shader RL_LoadShader(const char *vsFileName, const char *fsFileName) // Load shader from files and bind default locations
{
    return (LoadShader(vsFileName, fsFileName));
}
Shader RL_LoadShaderFromMemory(const char *vsCode, const char *fsCode) // Load shader from code strings and bind default locations
{
    return (LoadShaderFromMemory(vsCode, fsCode));
}
i32 RL_GetShaderLocation(Shader shader, const char *uniformName) // Get shader uniform location
{
    return (GetShaderLocation(shader, uniformName));
}
i32 RL_GetShaderLocationAttrib(Shader shader, const char *attribName) // Get shader attribute location
{
    return (GetShaderLocationAttrib(shader, attribName));
}
void RL_SetShaderValue(Shader shader, i32 locIndex, const void *value, i32 uniformType) // Set shader uniform value
{
    SetShaderValue(shader, locIndex, value, uniformType);
}
void RL_SetShaderValueV(Shader shader, i32 locIndex, const void *value, i32 uniformType, i32 count) // Set shader uniform value vector
{
    SetShaderValueV(shader, locIndex, value, uniformType, count);
}
void RL_SetShaderValueMatrix(Shader shader, i32 locIndex, Matrix mat) // Set shader uniform value (matrix 4x4)
{
    SetShaderValueMatrix(shader, locIndex, mat);
}
void RL_SetShaderValueTexture(Shader shader, i32 locIndex, Texture2D texture) // Set shader uniform value for texture (sampler2d)
{
    SetShaderValueTexture(shader, locIndex, texture);
}
void RL_UnloadShader(Shader shader) // Unload shader from GPU memory (VRAM)
{
    UnloadShader(shader);
}

// Screen-space-related functions
Ray RL_GetMouseRay(Vector2 mousePosition, Camera camera) // Get a ray trace from mouse position
{
    return (GetMouseRay(mousePosition, camera));
}
Matrix RL_GetCameraMatrix(Camera camera) // Get camera transform matrix (view matrix)
{
    return (GetCameraMatrix(camera));
}
Matrix RL_GetCameraMatrix2D(Camera2D camera) // Get camera 2d transform matrix
{
    return (GetCameraMatrix2D(camera));
}
Vector2 RL_GetWorldToScreen(Vector3 position, Camera camera) // Get the screen space position for a 3d world space position
{
    return (GetWorldToScreen(position, camera));
}
Vector2 RL_GetScreenToWorld2D(Vector2 position, Camera2D camera) // Get the world space position for a 2d camera screen space position
{
    return (GetScreenToWorld2D(position, camera));
}
Vector2 RL_GetWorldToScreenEx(Vector3 position, Camera camera, i32 width, i32 height) // Get size position for a 3d world space position
{
    return (GetWorldToScreenEx(position, camera, width, height));
}
Vector2 RL_GetWorldToScreen2D(Vector2 position, Camera2D camera) // Get the screen space position for a 2d camera world space position
{
    return (GetWorldToScreen2D(position, camera));
}

// Timing-related functions
void RL_SetTargetFPS(i32 fps) // Set target FPS (maximum)
{
    SetTargetFPS(fps);
}
i32 RL_GetFPS(void) // Get current FPS
{
    return (GetFPS());
}
r32 RL_GetFrameTime(void) // Get time in seconds for last frame drawn (delta time)
{
    return (GetFrameTime());
}
r64 RL_GetTime(void) // Get elapsed time in seconds since InitWindow()
{
    return (GetTime());
}

// Misc. functions
i32 RL_GetRandomValue(i32 min, i32 max) // Get a random value between min and max (both included)
{
    return (GetRandomValue(min, max));
}
void RL_SetRandomSeed(u32 seed) // Set the seed for the random number generator
{
    SetRandomSeed(seed);
}
void RL_TakeScreenshot(const char *fileName) // Takes a screenshot of current screen (filename extension defines format)
{
    TakeScreenshot(fileName);
}
void RL_SetConfigFlags(u32 flags) // Setup init configuration flags (view FLAGS)
{
    SetConfigFlags(flags);
}

void RL_SetTraceLogLevel(i32 logLevel) // Set the current threshold (minimum) log level
{
    SetTraceLogLevel(logLevel);
}
void *RL_MemAlloc(i32 size) // Internal memory allocator
{
    return (MemAlloc(size));
}
void *RL_MemRealloc(void *ptr, i32 size) // Internal memory reallocator
{
    return (MemRealloc(ptr, size));
}
void RL_MemFree(void *ptr) // Internal memory free
{
    MemFree(ptr);
}

void RL_OpenURL(const char *url) // Open URL with default system browser (if available)
{
    OpenURL(url);
}

// Set custom callbacks
// WARNING: Callbacks setup is intended for advance users
void RL_SetTraceLogCallback(TraceLogCallback callback) // Set custom trace log
{
    SetTraceLogCallback(callback);
}

// Files management functions
unsigned char *RL_LoadFileData(const char *fileName, u32 *bytesRead) // Load file data as byte array (read)
{
    return (LoadFileData(fileName, bytesRead));
}
void RL_UnloadFileData(unsigned char *data) // Unload file data allocated by LoadFileData()
{
    UnloadFileData(data);
}
b32 RL_SaveFileData(const char *fileName, void *data, u32 bytesToWrite) // Save data to file from byte array (write), returns true on success
{
    return (SaveFileData(fileName, data, bytesToWrite));
}
b32 RL_ExportDataAsCode(const char *data, u32 size, const char *fileName) // Export data to code (.h), returns true on success
{
    return (ExportDataAsCode(data, size, fileName));
}
char *RL_LoadFileText(const char *fileName) // Load text data from file (read), returns a '\0' terminated string
{
    return (LoadFileText(fileName));
}
void RL_UnloadFileText(char *text) // Unload file text data allocated by LoadFileText()
{
    UnloadFileText(text);
}
b32 RL_SaveFileText(const char *fileName, char *text) // Save text data to file (write), string must be '\0' terminated, returns true on success
{
    return (SaveFileText(fileName, text));
}
b32 RL_FileExists(const char *fileName) // Check if file exists
{
    return (FileExists(fileName));
}
b32 RL_DirectoryExists(const char *dirPath) // Check if a directory path exists
{
    return (DirectoryExists(dirPath));
}
b32 RL_IsFileExtension(const char *fileName, const char *ext) // Check file extension (including point: .png, .wav)
{
    return (IsFileExtension(fileName, ext));
}
i32 RL_GetFileLength(const char *fileName) // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
{
    return (GetFileLength(fileName));
}
const char *RL_GetFileExtension(const char *fileName) // Get pointer to extension for a filename string (includes dot: '.png')
{
    return (GetFileExtension(fileName));
}
const char *RL_GetFileName(const char *filePath) // Get pointer to filename for a path string
{
    return (GetFileName(filePath));
}
const char *RL_GetFileNameWithoutExt(const char *filePath) // Get filename string without extension (uses static string)
{
    return (GetFileNameWithoutExt(filePath));
}
const char *RL_GetDirectoryPath(const char *filePath) // Get full path for a given fileName with path (uses static string)
{
    return (GetDirectoryPath(filePath));
}
const char *RL_GetPrevDirectoryPath(const char *dirPath) // Get previous directory path for a given path (uses static string)
{
    return (GetPrevDirectoryPath(dirPath));
}
const char *RL_GetWorkingDirectory(void) // Get current working directory (uses static string)
{
    return (GetWorkingDirectory());
}
const char *RL_GetApplicationDirectory(void) // Get the directory if the running application (uses static string)
{
    return (GetApplicationDirectory());
}
b32 RL_ChangeDirectory(const char *dir) // Change working directory, return true on success
{
    return (ChangeDirectory(dir));
}
b32 RL_IsPathFile(const char *path) // Check if a given path is a file or a directory
{
    return (IsPathFile(path));
}
FilePathList RL_LoadDirectoryFiles(const char *dirPath) // Load directory filepaths
{
    return (LoadDirectoryFiles(dirPath));
}
FilePathList RL_LoadDirectoryFilesEx(const char *basePath, const char *filter, b32 scanSubdirs) // Load directory filepaths with extension filtering and recursive directory scan
{
    return (LoadDirectoryFilesEx(basePath, filter, scanSubdirs));
}
void RL_UnloadDirectoryFiles(FilePathList files) // Unload filepaths
{
    UnloadDirectoryFiles(files);
}
b32 RL_IsFileDropped(void) // Check if a file has been dropped into window
{
    return (IsFileDropped());
}
FilePathList RL_LoadDroppedFiles(void) // Load dropped filepaths
{
    return (LoadDroppedFiles());
}

void RL_UnloadDroppedFiles(FilePathList files) // Unload dropped filepaths
{
    UnloadDroppedFiles(files);
}
long RL_GetFileModTime(const char *fileName) // Get file modification time (last write time)
{
    return (GetFileModTime(fileName));
}

// Compression/Encoding functionality
unsigned char *RL_CompressData(unsigned char *data, i32 dataSize, i32 *compDataSize) // Compress data (DEFLATE algorithm), memory must be MemFree()
{
    return (CompressData(data, dataSize, compDataSize));
}
unsigned char *RL_DecompressData(unsigned char *compData, i32 compDataSize, i32 *dataSize) // Decompress data (DEFLATE algorithm), memory must be MemFree()
{
    return (DecompressData(compData, compDataSize, dataSize));
}
char *RL_EncodeDataBase64(const unsigned char *data, i32 dataSize, i32 *outputSize) // Encode data to Base64 string, memory must be MemFree()
{
    return (EncodeDataBase64(data, dataSize, outputSize));
}
unsigned char *RL_DecodeDataBase64(const unsigned char *data, i32 *outputSize) // Decode Base64 string data, memory must be MemFree()
{
    return (DecodeDataBase64(data, outputSize));
}

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard
b32 RL_IsKeyPressed(i32 key) // Check if a key has been pressed once
{
    return (IsKeyPressed(key));
}
b32 RL_IsKeyDown(i32 key) // Check if a key is being pressed
{
    return (IsKeyDown(key));
}
b32 RL_IsKeyReleased(i32 key) // Check if a key has been released once
{
    return (IsKeyReleased(key));
}
b32 RL_IsKeyUp(i32 key) // Check if a key is NOT being pressed
{
    return (IsKeyUp(key));
}
void RL_SetExitKey(i32 key) // Set a custom key to exit program (default is ESC)
{
    SetExitKey(key);
}
i32 RL_GetKeyPressed(void) // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
{
    return (GetKeyPressed());
}
i32 RL_GetCharPressed(void) // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
{
    return (GetCharPressed());
}

// Input-related functions: gamepads
b32 RL_IsGamepadAvailable(i32 gamepad) // Check if a gamepad is available
{
    return (IsGamepadAvailable(gamepad));
}
const char *RL_GetGamepadName(i32 gamepad) // Get gamepad internal name id
{
    return (GetGamepadName(gamepad));
}
b32 RL_IsGamepadButtonPressed(i32 gamepad, i32 button) // Check if a gamepad button has been pressed once
{
    return (IsGamepadButtonPressed(gamepad, button));
}
b32 RL_IsGamepadButtonDown(i32 gamepad, i32 button) // Check if a gamepad button is being pressed
{
    return (IsGamepadButtonDown(gamepad, button));
}
b32 RL_IsGamepadButtonReleased(i32 gamepad, i32 button) // Check if a gamepad button has been released once
{
    return (IsGamepadButtonReleased(gamepad, button));
}
b32 RL_IsGamepadButtonUp(i32 gamepad, i32 button) // Check if a gamepad button is NOT being pressed
{
    return (IsGamepadButtonUp(gamepad, button));
}
i32 RL_GetGamepadButtonPressed(void) // Get the last gamepad button pressed
{
    return (GetGamepadButtonPressed());
}
i32 RL_GetGamepadAxisCount(i32 gamepad) // Get gamepad axis count for a gamepad
{
    return (GetGamepadAxisCount(gamepad));
}
r32 RL_GetGamepadAxisMovement(i32 gamepad, i32 axis) // Get axis movement value for a gamepad axis
{
    return (GetGamepadAxisMovement(gamepad, axis));
}
i32 RL_SetGamepadMappings(const char *mappings) // Set internal gamepad mappings (SDL_GameControllerDB)
{
    return (SetGamepadMappings(mappings));
}

// Input-related functions: mouse
b32 RL_IsMouseButtonPressed(i32 button) // Check if a mouse button has been pressed once
{
    return (IsMouseButtonPressed(button));
}
b32 RL_IsMouseButtonDown(i32 button) // Check if a mouse button is being pressed
{
    return (IsMouseButtonDown(button));
}
b32 RL_IsMouseButtonReleased(i32 button) // Check if a mouse button has been released once
{
    return (IsMouseButtonReleased(button));
}
b32 RL_IsMouseButtonUp(i32 button) // Check if a mouse button is NOT being pressed
{
    return (IsMouseButtonUp(button));
}
i32 RL_GetMouseX(void) // Get mouse position X
{
    return (GetMouseX());
}
i32 RL_GetMouseY(void) // Get mouse position Y
{
    return (GetMouseY());
}
Vector2 RL_GetMousePosition(void) // Get mouse position XY
{
    return (GetMousePosition());
}
Vector2 RL_GetMouseDelta(void) // Get mouse delta between frames
{
    return (GetMouseDelta());
}
void RL_SetMousePosition(i32 x, i32 y) // Set mouse position XY
{
    SetMousePosition(x, y);
}
void RL_SetMouseOffset(i32 offsetX, i32 offsetY) // Set mouse offset
{
    SetMouseOffset(offsetX, offsetY);
}
void RL_SetMouseScale(r32 scaleX, r32 scaleY) // Set mouse scaling
{
    SetMouseScale(scaleX, scaleY);
}
r32 RL_GetMouseWheelMove(void) // Get mouse wheel movement for X or Y, whichever is larger
{
    return (GetMouseWheelMove());
}
Vector2 RL_GetMouseWheelMoveV(void) // Get mouse wheel movement for both X and Y
{
    return (GetMouseWheelMoveV());
}
void RL_SetMouseCursor(i32 cursor) // Set mouse cursor
{
    SetMouseCursor(cursor);
}

// Input-related functions: touch
i32 RL_GetTouchX(void) // Get touch position X for touch point 0 (relative to screen size)
{
    return (GetTouchX());
}
i32 RL_GetTouchY(void) // Get touch position Y for touch point 0 (relative to screen size)
{
    return (GetTouchY());
}
Vector2 RL_GetTouchPosition(i32 index) // Get touch position XY for a touch point index (relative to screen size)
{
    return (GetTouchPosition(index));
}
i32 RL_GetTouchPointId(i32 index) // Get touch point identifier for given index
{
    return (GetTouchPointId(index));
}
i32 RL_GetTouchPointCount(void) // Get number of touch points
{
    return (GetTouchPointCount());
}

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: rgestures)
//------------------------------------------------------------------------------------
void RL_SetGesturesEnabled(u32 flags) // Enable a set of gestures using flags
{
    SetGesturesEnabled(flags);
}
b32 RL_IsGestureDetected(i32 gesture) // Check if a gesture have been detected
{
    return (IsGestureDetected(gesture));
}
i32 RL_GetGestureDetected(void) // Get latest detected gesture
{
    return (GetGestureDetected());
}
r32 RL_GetGestureHoldDuration(void) // Get gesture hold time in milliseconds
{
    return (GetGestureHoldDuration());
}
Vector2 RL_GetGestureDragVector(void) // Get gesture drag vector
{
    return (GetGestureDragVector());
}
r32 RL_GetGestureDragAngle(void) // Get gesture drag angle
{
    return (GetGestureDragAngle());
}
Vector2 RL_GetGesturePinchVector(void) // Get gesture pinch delta
{
    return (GetGesturePinchVector());
}
r32 RL_GetGesturePinchAngle(void) // Get gesture pinch angle
{
    return (GetGesturePinchAngle());
}

//------------------------------------------------------------------------------------
// Camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
void RL_SetCameraMode(Camera camera, i32 mode) // Set camera mode (multiple camera modes available)
{
    SetCameraMode(camera, mode);
}
void RL_UpdateCamera(Camera *camera) // Update camera position for selected mode
{
    UpdateCamera(camera);
}

void RL_SetCameraPanControl(i32 keyPan) // Set camera pan key to combine with mouse movement (free camera)
{
    SetCameraPanControl(keyPan);
}
void RL_SetCameraAltControl(i32 keyAlt) // Set camera alt key to combine with mouse movement (free camera)
{
    SetCameraAltControl(keyAlt);
}
void RL_SetCameraSmoothZoomControl(i32 keySmoothZoom) // Set camera smooth zoom key to combine with mouse (free camera)
{
    SetCameraSmoothZoomControl(keySmoothZoom);
}
void RL_SetCameraMoveControls(i32 keyFront, i32 keyBack, i32 keyRight, i32 keyLeft, i32 keyUp, i32 keyDown) // Set camera move controls (1st person and 3rd person cameras)
{
    SetCameraMoveControls(keyFront, keyBack, keyRight, keyLeft, keyUp, keyDown);
}

// True if P is left of the line defined by A and B
internal inline b32 IsLeft(Vector2 A, Vector2 B, Vector2 P)
{
    return (((B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x)) > 0.0f);
}

/***
 * SHAPES
 */
// Set texture and Rec to be used on shapes drawing
// NOTE: It can be useful when using basic shapes and one single font,
// defining a font u8 white Rec would allow drawing everything in a single draw call
void RL_SetShapesTexture(Texture2D texture, Rec source) // Set texture and Rec to be used on shapes drawing
{
    SetShapesTexture(texture, source);
}

// Basic shapes drawing functions
void RL_DrawPixel(i32 posX, i32 posY, Color color) // Draw a pixel
{
    DrawPixel(posX, posY, color);
}
void RL_DrawPixelV(Vector2 position, Color color) // Draw a pixel (Vector version)
{
    DrawPixelV(position, color);
}
void RL_DrawLine(i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color) // Draw a line
{
    DrawLine(startPosX, startPosY, endPosX, endPosY, color);
}
void RL_DrawLineV(Vector2 startPos, Vector2 endPos, Color color) // Draw a line (Vector version)
{
    DrawLineV(startPos, endPos, color);
}
void RL_DrawLineEx(Vector2 startPos, Vector2 endPos, r32 thick, Color color) // Draw a line defining thickness
{
    DrawLineEx(startPos, endPos, thick, color);
}
void RL_DrawLineBezier(Vector2 startPos, Vector2 endPos, r32 thick, Color color) // Draw a line using cubic-bezier curves in-out
{
    DrawLineBezier(startPos, endPos, thick, color);
}
void RL_DrawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, r32 thick, Color color) // Draw line using quadratic bezier curves with a control point
{
    DrawLineBezierQuad(startPos, endPos, controlPos, thick, color);
}
void RL_DrawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, r32 thick, Color color) // Draw line using cubic bezier curves with 2 control points
{
    DrawLineBezierCubic(startPos, endPos, startControlPos, endControlPos, thick, color);
}
void RL_DrawLineStrip(Vector2 *points, i32 pointCount, Color color) // Draw lines sequence
{
    DrawLineStrip(points, pointCount, color);
}
void RL_DrawCircle(i32 centerX, i32 centerY, r32 radius, Color color) // Draw a color-filled circle
{
    DrawCircle(centerX, centerY, radius, color);
}
void RL_DrawCircleSector(Vector2 center, r32 radius, r32 startAngle, r32 endAngle, i32 segments, Color color) // Draw a piece of a circle
{
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}
void RL_DrawCircleSectorLines(Vector2 center, r32 radius, r32 startAngle, r32 endAngle, i32 segments, Color color) // Draw circle sector outline
{
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}
void RL_DrawCircleGradient(i32 centerX, i32 centerY, r32 radius, Color color1, Color color2) // Draw a gradient-filled circle
{
    DrawCircleGradient(centerX, centerY, radius, color1, color2);
}
void RL_DrawCircleV(Vector2 center, r32 radius, Color color) // Draw a color-filled circle (Vector version)
{
    DrawCircleV(center, radius, color);
}
void RL_DrawCircleLines(i32 centerX, i32 centerY, r32 radius, Color color) // Draw circle outline
{
    DrawCircleLines(centerX, centerY, radius, color);
}
void RL_DrawEllipse(i32 centerX, i32 centerY, r32 radiusH, r32 radiusV, Color color) // Draw ellipse
{
    DrawEllipse(centerX, centerY, radiusH, radiusV, color);
}
void RL_DrawEllipseLines(i32 centerX, i32 centerY, r32 radiusH, r32 radiusV, Color color) // Draw ellipse outline
{
    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
}
void RL_DrawRing(Vector2 center, r32 innerRadius, r32 outerRadius, r32 startAngle, r32 endAngle, i32 segments, Color color) // Draw ring
{
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}
void RL_DrawRingLines(Vector2 center, r32 innerRadius, r32 outerRadius, r32 startAngle, r32 endAngle, i32 segments, Color color) // Draw ring outline
{
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}
void RL_DrawRectangle(i32 posX, i32 posY, i32 width, i32 height, Color color) // Draw a color-filled Rec
{
    DrawRectangle(posX, posY, width, height, color);
}
void RL_DrawRectangleV(Vector2 position, Vector2 size, Color color) // Draw a color-filled Rec (Vector version)
{
    DrawRectangleV(position, size, color);
}
void RL_DrawRectangleRec(Rec rec, Color color) // Draw a color-filled Rec
{
    DrawRectangleRec(rec, color);
}
void RL_DrawRectanglePro(Rec rec, Vector2 origin, r32 rotation, Color color) // Draw a color-filled Rec with pro parameters
{
    DrawRectanglePro(rec, origin, rotation, color);
}
void RL_DrawRectangleGradientV(i32 posX, i32 posY, i32 width, i32 height, Color color1, Color color2) // Draw a vertical-gradient-filled Rec
{
    DrawRectangleGradientV(posX, posY, width, height, color1, color2);
}
void RL_DrawRectangleGradientH(i32 posX, i32 posY, i32 width, i32 height, Color color1, Color color2) // Draw a horizontal-gradient-filled Rec
{
    DrawRectangleGradientH(posX, posY, width, height, color1, color2);
}
void RL_DrawRectangleGradientEx(Rec rec, Color col1, Color col2, Color col3, Color col4) // Draw a gradient-filled Rec with custom vertex colors
{
    DrawRectangleGradientEx(rec, col1, col2, col3, col4);
}
void RL_DrawRectangleLines(i32 posX, i32 posY, i32 width, i32 height, Color color) // Draw Rec outline
{
    DrawRectangleLines(posX, posY, width, height, color);
}
void RL_DrawRectangleLinesEx(Rec rec, r32 lineThickness, Color color) // Draw Rec outline with extended parameters
{
    DrawRectangleLinesEx(rec, lineThickness, color);
}
void RL_DrawRectangleRounded(Rec rec, r32 roundness, i32 segments, Color color) // Draw Rec with rounded edges
{
    DrawRectangleRounded(rec, roundness, segments, color);
}
void RL_DrawRectangleRoundedLines(Rec rec, r32 roundness, i32 segments, r32 lineThick, Color color) // Draw Rec with rounded edges outline
{
    DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
}
void RL_DrawTriangle(Vector2 A, Vector2 B, Vector2 C, Color color) // Draw a color-filled triangle (vertex in counter-clockwise order!)
{
    if (IsLeft(A, B, C) == false)
    {
        DrawTriangle(C, B, A, color);
    }
    else if (IsLeft(B, C, A) == false)
    {
        DrawTriangle(B, C, A, color);
    }
    else if (IsLeft(C, A, B))
    {
        DrawTriangle(A, C, B, color);
    }
    else
    {
        DrawTriangle(A, B, C, color);
    }
}
void DrawTriangleRotated(Vector2 A, Vector2 B, Vector2 C, Vector2 origin, r32 rotation, Color color) // Draw a color-filled triangle (vertex in counter-clockwise order!)
{
    rlPushMatrix();
    rlTranslatef(origin.x, origin.y, 0.0f);
    rotation *= 180.0f / PI;
    rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-origin.x, -origin.y, 0.0f);
    if (IsLeft(A, B, C) == false)
    {
        DrawTriangle(C, B, A, color);
        rlPopMatrix();
    }
    else if (IsLeft(B, C, A) == false)
    {
        DrawTriangle(B, C, A, color);
        rlPopMatrix();
    }
    else if (IsLeft(C, A, B))
    {
        DrawTriangle(A, C, B, color);
        rlPopMatrix();
    }
    else
    {
        DrawTriangle(A, B, C, color);
        rlPopMatrix();
    }
}
void RL_DrawTriangleLines(Vector2 A, Vector2 B, Vector2 C, Color color) // Draw triangle outline (vertex in counter-clockwise order!)
{
    if (IsLeft(A, B, C) == false)
    {
        DrawTriangleLines(C, B, A, color);
    }
    else if (IsLeft(B, C, A) == false)
    {
        DrawTriangleLines(B, C, A, color);
    }
    else if (IsLeft(C, A, B))
    {
        DrawTriangleLines(A, C, B, color);
    }
    else
    {
        DrawTriangleLines(A, B, C, color);
    }
}
void DrawTriangleLinesRotated(Vector2 A, Vector2 B, Vector2 C, Vector2 origin, r32 rotation, Color color) // Draw a color-filled triangle (vertex in counter-clockwise order!)
{
    rlPushMatrix();
    rlTranslatef(origin.x, origin.y, 0.0f);
    rotation *= 180.0f / PI;
    rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-origin.x, -origin.y, 0.0f);
    if (IsLeft(A, B, C) == false)
    {
        DrawTriangleLines(C, B, A, color);
        rlPopMatrix();
    }
    else if (IsLeft(B, C, A) == false)
    {
        DrawTriangleLines(B, C, A, color);
        rlPopMatrix();
    }
    else if (IsLeft(C, A, B))
    {
        DrawTriangleLines(A, C, B, color);
        rlPopMatrix();
    }
    else
    {
        DrawTriangleLines(A, B, C, color);
        rlPopMatrix();
    }
}
void RL_DrawTriangleFan(Vector2 *points, i32 pointCount, Color color) // Draw a triangle fan defined by points (first vertex is the center)
{
    DrawTriangleFan(points, pointCount, color);
}
void RL_DrawTriangleStrip(Vector2 *points, i32 pointCount, Color color) // Draw a triangle strip defined by points
{
    DrawTriangleStrip(points, pointCount, color);
}
void RL_DrawPoly(Vector2 center, i32 sides, r32 radius, r32 rotation, Color color) // Draw a regular polygon (Vector version)
{
    DrawPoly(center, sides, radius, rotation, color);
}
void RL_DrawPolyLines(Vector2 center, i32 sides, r32 radius, r32 rotation, Color color) // Draw a polygon outline of n sides
{
    DrawPolyLines(center, sides, radius, rotation, color);
}
void RL_DrawPolyLinesEx(Vector2 center, i32 sides, r32 radius, r32 rotation, r32 lineThick, Color color) // Draw a polygon outline of n sides with extended parameters
{
    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
}

// Basic shapes collision detection functions
b32 RL_CheckCollisionRecs(Rec rec1, Rec rec2) // Check collision between two Recs
{
    return (CheckCollisionRecs(rec1, rec2));
}
b32 RL_CheckCollisionCircles(Vector2 center1, r32 radius1, Vector2 center2, r32 radius2) // Check collision between two circles
{
    return (CheckCollisionCircles(center1, radius1, center2, radius2));
}
b32 RL_CheckCollisionCircleRec(Vector2 center, r32 radius, Rec rec) // Check collision between circle and Rec
{
    return (CheckCollisionCircleRec(center, radius, rec));
}
b32 RL_CheckCollisionPointRec(Vector2 point, Rec rec) // Check if point is inside Rec
{
    return (CheckCollisionPointRec(point, rec));
}
b32 RL_CheckCollisionPointCircle(Vector2 point, Vector2 center, r32 radius) // Check if point is inside circle
{
    return (CheckCollisionPointCircle(point, center, radius));
}
b32 RL_CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3) // Check if point is inside a triangle
{
    return (CheckCollisionPointTriangle(point, p1, p2, p3));
}
b32 RL_CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint) // Check the collision between two lines defined by two points each, returns collision point by reference
{
    return (CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, collisionPoint));
}
b32 RL_CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, i32 threshold) // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
{
    return (CheckCollisionPointLine(point, p1, p2, threshold));
}
Rec RL_GetCollisionRec(Rec rec1, Rec rec2) // Get collision Rec for two Recs collision
{
    return (GetCollisionRec(rec1, rec2));
}

/***
 * Textures
 */
// Image loading functions
// NOTE: This functions do not require GPU access
Image RL_LoadImage(const char *fileName) // Load image from file into CPU memory (RAM)
{
    return (LoadImage(fileName));
}
Image RL_LoadImageRaw(const char *fileName, i32 width, i32 height, i32 format, i32 headerSize) // Load image from RAW file data
{
    return (LoadImageRaw(fileName, width, height, format, headerSize));
}
Image RL_LoadImageAnim(const char *fileName, i32 *frames) // Load image sequence from file (frames appended to image.data)
{
    return (LoadImageAnim(fileName, frames));
}
Image RL_LoadImageFromMemory(const char *fileType, const unsigned char *fileData, i32 dataSize) // Load image from memory buffer, fileType refers to extension: i.e. '.png'
{
    return (LoadImageFromMemory(fileType, fileData, dataSize));
}
Image RL_LoadImageFromTexture(Texture2D texture) // Load image from GPU texture data
{
    return (LoadImageFromTexture(texture));
}
Image RL_LoadImageFromScreen(void) // Load image from screen buffer and (screenshot)
{
    return (LoadImageFromScreen());
}
void RL_UnloadImage(Image image) // Unload image from CPU memory (RAM)
{
    UnloadImage(image);
}
b32 RL_ExportImage(Image image, const char *fileName) // Export image data to file, returns true on success
{
    return (ExportImage(image, fileName));
}
b32 RL_ExportImageAsCode(Image image, const char *fileName) // Export image as code file defining an array of bytes, returns true on success
{
    return (ExportImageAsCode(image, fileName));
}

// Image generation functions
Image RL_GenImageColor(i32 width, i32 height, Color color) // Generate image: plain color
{
    return (GenImageColor(width, height, color));
}
Image RL_GenImageGradientV(i32 width, i32 height, Color top, Color bottom) // Generate image: vertical gradient
{
    return (GenImageGradientV(width, height, top, bottom));
}
Image RL_GenImageGradientH(i32 width, i32 height, Color left, Color right) // Generate image: horizontal gradient
{
    return (GenImageGradientH(width, height, left, right));
}
Image RL_GenImageGradientRadial(i32 width, i32 height, r32 density, Color inner, Color outer) // Generate image: radial gradient
{
    return (GenImageGradientRadial(width, height, density, inner, outer));
}
Image RL_GenImageChecked(i32 width, i32 height, i32 checksX, i32 checksY, Color col1, Color col2) // Generate image: checked
{
    return (GenImageChecked(width, height, checksX, checksY, col1, col2));
}
Image RL_GenImageWhiteNoise(i32 width, i32 height, r32 factor) // Generate image: white noise
{
    return (GenImageWhiteNoise(width, height, factor));
}
Image RL_GenImageCellular(i32 width, i32 height, i32 tileSize) // Generate image: cellular algorithm, bigger tileSize means bigger cells
{
    return (GenImageCellular(width, height, tileSize));
}

// Image manipulation functions
Image RL_ImageCopy(Image image) // Create an image duplicate (useful for transformations)
{
    return (ImageCopy(image));
}
Image RL_ImageFromImage(Image image, Rec rec) // Create an image from another image piece
{
    return (ImageFromImage(image, rec));
}
Image RL_ImageText(const char *text, i32 fontSize, Color color) // Create an image from text (default font)
{
    return (ImageText(text, fontSize, color));
}
Image RL_ImageTextEx(Font font, const char *text, r32 fontSize, r32 spacing, Color tint) // Create an image from text (custom sprite font)
{
    return (ImageTextEx(font, text, fontSize, spacing, tint));
}
void RL_ImageFormat(Image *image, i32 newFormat) // Convert image data to desired format
{
    ImageFormat(image, newFormat);
}
void RL_ImageToPOT(Image *image, Color fill) // Convert image to POT (power-of-two)
{
    ImageToPOT(image, fill);
}
void RL_ImageCrop(Image *image, Rec crop) // Crop an image to a defined Rec
{
    ImageCrop(image, crop);
}
void RL_ImageAlphaCrop(Image *image, r32 threshold) // Crop image depending on alpha value
{
    ImageAlphaCrop(image, threshold);
}
void RL_ImageAlphaClear(Image *image, Color color, r32 threshold) // Clear alpha channel to desired color
{
    ImageAlphaClear(image, color, threshold);
}
void RL_ImageAlphaMask(Image *image, Image alphaMask) // Apply alpha mask to image
{
    ImageAlphaMask(image, alphaMask);
}
void RL_ImageAlphaPremultiply(Image *image) // Premultiply alpha channel
{
    ImageAlphaPremultiply(image);
}
void RL_ImageResize(Image *image, i32 newWidth, i32 newHeight) // Resize image (Bicubic scaling algorithm)
{
    ImageResize(image, newWidth, newHeight);
}
void RL_ImageResizeNN(Image *image, i32 newWidth, i32 newHeight) // Resize image (Nearest-Neighbor scaling algorithm)
{
    ImageResizeNN(image, newWidth, newHeight);
}
void RL_ImageResizeCanvas(Image *image, i32 newWidth, i32 newHeight, i32 offsetX, i32 offsetY, Color fill) // Resize canvas and fill with color
{
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);
}
void RL_ImageMipmaps(Image *image) // Compute all mipmap levels for a provided image
{
    ImageMipmaps(image);
}
void RL_ImageDither(Image *image, i32 rBpp, i32 gBpp, i32 bBpp, i32 aBpp) // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
{
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
}
void RL_ImageFlipVertical(Image *image) // Flip image vertically
{
    ImageFlipVertical(image);
}
void RL_ImageFlipHorizontal(Image *image) // Flip image horizontally
{
    ImageFlipHorizontal(image);
}
void RL_ImageRotateCW(Image *image) // Rotate image clockwise 90deg
{
    ImageRotateCW(image);
}
void RL_ImageRotateCCW(Image *image) // Rotate image counter-clockwise 90deg
{
    ImageRotateCCW(image);
}
void RL_ImageColorTint(Image *image, Color color) // Modify image color: tint
{
    ImageColorTint(image, color);
}
void RL_ImageColorInvert(Image *image) // Modify image color: invert
{
    ImageColorInvert(image);
}
void RL_ImageColorGrayscale(Image *image) // Modify image color: grayscale
{
    ImageColorGrayscale(image);
}
void RL_ImageColorContrast(Image *image, r32 contrast) // Modify image color: contrast (-100 to 100)
{
    ImageColorContrast(image, contrast);
}
void RL_ImageColorBrightness(Image *image, i32 brightness) // Modify image color: brightness (-255 to 255)
{
    ImageColorBrightness(image, brightness);
}
void RL_ImageColorReplace(Image *image, Color color, Color replace) // Modify image color: replace color
{
    ImageColorReplace(image, color, replace);
}
Color *RL_LoadImageColors(Image image) // Load color data from image as a Color array (RGBA - 32bit)
{
    return (LoadImageColors(image));
}
Color *RL_LoadImagePalette(Image image, i32 maxPaletteSize, i32 *colorCount) // Load colors palette from image as a Color array (RGBA - 32bit)
{
    return (LoadImagePalette(image, maxPaletteSize, colorCount));
}
void RL_UnloadImageColors(Color *colors) // Unload color data loaded with LoadImageColors()
{
    UnloadImageColors(colors);
}
void RL_UnloadImagePalette(Color *colors) // Unload colors palette loaded with LoadImagePalette()
{
    UnloadImagePalette(colors);
}
Rec RL_GetImageAlphaBorder(Image image, r32 threshold) // Get image alpha border Rec
{
    return (GetImageAlphaBorder(image, threshold));
}
Color RL_GetImageColor(Image image, i32 x, i32 y) // Get image pixel color at (x, y) position
{
    return (GetImageColor(image, x, y));
}

// Image drawing functions
// NOTE: Image software-rendering functions (CPU)
void RL_ImageClearBackground(Image *dst, Color color) // Clear image background with given color
{
    ImageClearBackground(dst, color);
}
void RL_ImageDrawPixel(Image *dst, i32 posX, i32 posY, Color color) // Draw pixel within an image
{
    ImageDrawPixel(dst, posX, posY, color);
}
void RL_ImageDrawPixelV(Image *dst, Vector2 position, Color color) // Draw pixel within an image (Vector version)
{
    ImageDrawPixelV(dst, position, color);
}
void RL_ImageDrawLine(Image *dst, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color) // Draw line within an image
{
    ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);
}
void RL_ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color) // Draw line within an image (Vector version)
{
    ImageDrawLineV(dst, start, end, color);
}
void RL_ImageDrawCircle(Image *dst, i32 centerX, i32 centerY, i32 radius, Color color) // Draw circle within an image
{
    ImageDrawCircle(dst, centerX, centerY, radius, color);
}
void RL_ImageDrawCircleV(Image *dst, Vector2 center, i32 radius, Color color) // Draw circle within an image (Vector version)
{
    ImageDrawCircleV(dst, center, radius, color);
}
void RL_ImageDrawRectangle(Image *dst, i32 posX, i32 posY, i32 width, i32 height, Color color) // Draw Rec within an image
{
    ImageDrawRectangle(dst, posX, posY, width, height, color);
}
void RL_ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color) // Draw Rec within an image (Vector version)
{
    ImageDrawRectangleV(dst, position, size, color);
}
void RL_ImageDrawRectangleRec(Image *dst, Rec rec, Color color) // Draw Rec within an image
{
    ImageDrawRectangleRec(dst, rec, color);
}
void RL_ImageDrawRectangleLines(Image *dst, Rec rec, i32 thick, Color color) // Draw Rec lines within an image
{
    ImageDrawRectangleLines(dst, rec, thick, color);
}
void RL_ImageDraw(Image *dst, Image src, Rec srcRec, Rec dstRec, Color tint) // Draw a source image within a destination image (tint applied to source)
{
    ImageDraw(dst, src, srcRec, dstRec, tint);
}
void RL_ImageDrawText(Image *dst, const char *text, i32 posX, i32 posY, i32 fontSize, Color color) // Draw text (using default font) within an image (destination)
{
    ImageDrawText(dst, text, posX, posY, fontSize, color);
}
void RL_ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, r32 fontSize, r32 spacing, Color tint) // Draw text (custom sprite font) within an image (destination)
{
    ImageDrawTextEx(dst, font, text, position, fontSize, spacing, tint);
}

// Texture loading functions
// NOTE: These functions require GPU access
Texture2D RL_LoadTexture(const char *fileName) // Load texture from file into GPU memory (VRAM)
{
    return (LoadTexture(fileName));
}
Texture2D RL_LoadTextureFromImage(Image image) // Load texture from image data
{
    return (LoadTextureFromImage(image));
}
TextureCubemap RL_LoadTextureCubemap(Image image, i32 layout) // Load cubemap from image, multiple image cubemap layouts supported
{
    return (LoadTextureCubemap(image, layout));
}
RenderTexture2D RL_LoadRenderTexture(i32 width, i32 height) // Load texture for rendering (framebuffer)
{
    return (LoadRenderTexture(width, height));
}
void RL_UnloadTexture(Texture2D texture) // Unload texture from GPU memory (VRAM)
{
    UnloadTexture(texture);
}
void RL_UnloadRenderTexture(RenderTexture2D target) // Unload render texture from GPU memory (VRAM)
{
    UnloadRenderTexture(target);
}
void RL_UpdateTexture(Texture2D texture, const void *pixels) // Update GPU texture with new data
{
    UpdateTexture(texture, pixels);
}
void RL_UpdateTextureRec(Texture2D texture, Rec rec, const void *pixels) // Update GPU texture Rec with new data
{
    UpdateTextureRec(texture, rec, pixels);
}

// Texture configuration functions
void RL_GenTextureMipmaps(Texture2D *texture) // Generate GPU mipmaps for a texture
{
    GenTextureMipmaps(texture);
}
void RL_SetTextureFilter(Texture2D texture, i32 filter) // Set texture scaling filter mode
{
    SetTextureFilter(texture, filter);
}
void RL_SetTextureWrap(Texture2D texture, i32 wrap) // Set texture wrapping mode
{
    SetTextureWrap(texture, wrap);
}

// Texture drawing functions
void RL_DrawTexture(Texture2D texture, i32 posX, i32 posY, Color tint) // Draw a Texture2D
{
    DrawTexture(texture, posX, posY, tint);
}
void RL_DrawTextureV(Texture2D texture, Vector2 position, Color tint) // Draw a Texture2D with position defined as Vector2
{
    DrawTextureV(texture, position, tint);
}
void RL_DrawTextureEx(Texture2D texture, Vector2 position, r32 rotation, r32 scale, Color tint) // Draw a Texture2D with extended parameters
{
    DrawTextureEx(texture, position, rotation, scale, tint);
}
void DrawTextureRotatedScaled(Texture2D texture, Vector2 position, Vector2 origin, r32 rotation, r32 scale, Color tint)
{
    rlPushMatrix();
    rlTranslatef(origin.x, origin.y, 0.0f);
    rotation *= 180.0f / PI;
    rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-origin.x, -origin.y, 0.0f);
    RL_DrawTextureEx(texture, position, 0.0f, scale, tint);
    rlPopMatrix();
}
void DrawTextureRotated(Texture2D texture, Vector2 position, Vector2 origin, r32 rotation, Color tint) // Draw a Texture2D with rotation around an origin
{
    rlPushMatrix();
    rlTranslatef(origin.x, origin.y, 0.0f);
    rotation *= 180.0f / PI;
    rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-origin.x, -origin.y, 0.0f);
    RL_DrawTextureV(texture, position, tint);
    rlPopMatrix();
}
void RL_DrawTextureRec(Texture2D texture, Rec source, Vector2 position, Color tint) // Draw a part of a texture defined by a Rec
{
    DrawTextureRec(texture, source, position, tint);
}
void RL_DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rec quad, Color tint) // Draw texture quad with tiling and offset parameters
{
    DrawTextureQuad(texture, tiling, offset, quad, tint);
}
void RL_DrawTextureTiled(Texture2D texture, Rec source, Rec dest, Vector2 origin, r32 rotation, r32 scale, Color tint) // Draw part of a texture (defined by a Rec) with rotation and scale tiled into dest.
{
    DrawTextureTiled(texture, source, dest, origin, rotation, scale, tint);
}
void RL_DrawTexturePro(Texture2D texture, Rec source, Rec dest, Vector2 origin, r32 rotation, Color tint) // Draw a part of a texture defined by a Rec with 'pro' parameters
{
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
void RL_DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rec dest, Vector2 origin, r32 rotation, Color tint) // Draws a texture (or part of it) that stretches or shrinks nicely
{
    DrawTextureNPatch(texture, nPatchInfo, dest, origin, rotation, tint);
}
void RL_DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, i32 pointCount, Color tint) // Draw a textured polygon
{
    DrawTexturePoly(texture, center, points, texcoords, pointCount, tint);
}

// Color/pixel related functions
Color RL_Fade(Color color, r32 alpha) // Get color with alpha applied, alpha goes from 0.0f to 1.0f
{
    return (Fade(color, alpha));
}
i32 RL_ColorToInt(Color color) // Get hexadecimal value for a Color
{
    return (ColorToInt(color));
}
Vector4 RL_ColorNormalize(Color color) // Get Color normalized as r32 [0..1]
{
    return (ColorNormalize(color));
}
Color RL_ColorFromNormalized(Vector4 normalized) // Get Color from normalized values [0..1]
{
    return (ColorFromNormalized(normalized));
}
Vector3 RL_ColorToHSV(Color color) // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
{
    return (ColorToHSV(color));
}
Color RL_ColorFromHSV(r32 hue, r32 saturation, r32 value) // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
{
    return (ColorFromHSV(hue, saturation, value));
}
Color RL_ColorAlpha(Color color, r32 alpha) // Get color with alpha applied, alpha goes from 0.0f to 1.0f
{
    return (ColorAlpha(color, alpha));
}
Color RL_ColorAlphaBlend(Color dst, Color src, Color tint) // Get src alpha-blended into dst color with tint
{
    return (ColorAlphaBlend(dst, src, tint));
}
Color RL_GetColor(u32 hexValue) // Get Color structure from hexadecimal value
{
    return (GetColor(hexValue));
}
Color RL_GetPixelColor(void *srcPtr, i32 format) // Get Color from a source pixel pointer of certain format
{
    return (GetPixelColor(srcPtr, format));
}
void RL_SetPixelColor(void *dstPtr, Color color, i32 format) // Set color formatted into destination pixel pointer
{
    SetPixelColor(dstPtr, color, format);
}
i32 RL_GetPixelDataSize(i32 width, i32 height, i32 format) // Get pixel data size in bytes for certain format
{
    return (GetPixelDataSize(width, height, format));
}

/***
 * Text
 */

// Font loading/unloading functions
Font RL_GetFontDefault(void) // Get the default Font
{
    return (GetFontDefault());
}
Font RL_LoadFont(const char *fileName) // Load font from file into GPU memory (VRAM)
{
    return (LoadFont(fileName));
}
Font RL_LoadFontEx(const char *fileName, i32 fontSize, i32 *fontChars, i32 glyphCount) // Load font from file with extended parameters, use NULL for fontChars and 0 for glyphCount to load the default character set
{
    return (LoadFontEx(fileName, fontSize, fontChars, glyphCount));
}
Font RL_LoadFontFromImage(Image image, Color key, i32 firstChar) // Load font from Image (XNA style)
{
    return (LoadFontFromImage(image, key, firstChar));
}
Font RL_LoadFontFromMemory(const char *fileType, const unsigned char *fileData, i32 dataSize, i32 fontSize, i32 *fontChars, i32 glyphCount) // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
{
    return (LoadFontFromMemory(fileType, fileData, dataSize, fontSize, fontChars, glyphCount));
}
GlyphInfo *RL_LoadFontData(const unsigned char *fileData, i32 dataSize, i32 fontSize, i32 *fontChars, i32 glyphCount, i32 type) // Load font data for further use
{
    return (LoadFontData(fileData, dataSize, fontSize, fontChars, glyphCount, type));
}
Image RL_GenImageFontAtlas(const GlyphInfo *chars, Rec **recs, i32 glyphCount, i32 fontSize, i32 padding, i32 packMethod) // Generate image font atlas using chars info
{
    return (GenImageFontAtlas(chars, recs, glyphCount, fontSize, padding, packMethod));
}
void RL_UnloadFontData(GlyphInfo *chars, i32 glyphCount) // Unload font chars info data (RAM)
{
    UnloadFontData(chars, glyphCount);
}
void RL_UnloadFont(Font font) // Unload font from GPU memory (VRAM)
{
    UnloadFont(font);
}
b32 RL_ExportFontAsCode(Font font, const char *fileName) // Export font as code file, returns true on success
{
    return (ExportFontAsCode(font, fileName));
}

// Text drawing functions
void RL_DrawFPS(i32 posX, i32 posY) // Draw current FPS
{
    DrawFPS(posX, posY);
}
void RL_DrawText(const string &text, i32 posX, i32 posY, i32 fontSize, Color color) // Draw text (using default font)
{
    DrawText(text.c_str(), posX, posY, fontSize, color);
}
void RL_DrawTextEx(Font font, const string &text, Vector2 position, r32 fontSize, r32 spacing, Color tint) // Draw text using font and additional parameters
{
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
}
void RL_DrawTextPro(Font font, const string &text, Vector2 position, Vector2 origin, r32 rotation, r32 fontSize, r32 spacing, Color tint) // Draw text using Font and pro parameters (rotation)
{
    DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
}
void RL_DrawTextCodepoint(Font font, i32 codepoint, Vector2 position, r32 fontSize, Color tint) // Draw one character (codepoint)
{
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
}
void RL_DrawTextCodepoints(Font font, const i32 *codepoints, i32 count, Vector2 position, r32 fontSize, r32 spacing, Color tint) // Draw multiple character (codepoint)
{
    DrawTextCodepoints(font, codepoints, count, position, fontSize, spacing, tint);
}

// Text font info functions
i32 RL_MeasureText(const char *text, i32 fontSize) // Measure string width for default font
{
    return (MeasureText(text, fontSize));
}
Vector2 RL_MeasureTextEx(Font font, const char *text, r32 fontSize, r32 spacing) // Measure string size for Font
{
    return (MeasureTextEx(font, text, fontSize, spacing));
}
i32 RL_GetGlyphIndex(Font font, i32 codepoint) // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
{
    return (GetGlyphIndex(font, codepoint));
}
GlyphInfo RL_GetGlyphInfo(Font font, i32 codepoint) // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
{
    return (GetGlyphInfo(font, codepoint));
}
Rec RL_GetGlyphAtlasRec(Font font, i32 codepoint) // Get glyph Rec in font atlas for a codepoint (unicode character), fallback to '?' if not found
{
    return (GetGlyphAtlasRec(font, codepoint));
}

// Text codepoints management functions (unicode characters)
i32 *RL_LoadCodepoints(const char *text, i32 *count) // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
{
    return (LoadCodepoints(text, count));
}
void RL_UnloadCodepoints(i32 *codepoints) // Unload codepoints data from memory
{
    UnloadCodepoints(codepoints);
}
i32 RL_GetCodepointCount(const char *text) // Get total number of codepoints in a UTF-8 encoded string
{
    return (GetCodepointCount(text));
}
i32 RL_GetCodepoint(const char *text, i32 *bytesProcessed) // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
{
    return (GetCodepoint(text, bytesProcessed));
}
const char *RL_CodepointToUTF8(i32 codepoint, i32 *byteSize) // Encode one codepoint into UTF-8 byte array (array length returned as parameter)
{
    return (CodepointToUTF8(codepoint, byteSize));
}
char *RL_TextCodepointsToUTF8(const i32 *codepoints, i32 length) // Encode text as codepoints array into UTF-8 text string (WARNING: memory must be freed!)
{
    return (TextCodepointsToUTF8(codepoints, length));
}

// Text strings management functions (no UTF-8 strings, only byte chars)
// NOTE: Some strings allocate memory internally for returned strings, just be careful!
i32 RL_TextCopy(char *dst, const char *src) // Copy one string to another, returns bytes copied
{
    return (TextCopy(dst, src));
}
b32 RL_TextIsEqual(const char *text1, const char *text2) // Check if two text string are equal
{
    return (TextIsEqual(text1, text2));
}
u32 RL_TextLength(const char *text) // Get text length, checks for '\0' ending
{
    return (TextLength(text));
}
// const char *RL_TextFormat(const char *text, ...)                                        // Text formatting with variables (sprintf() style)
// {
//     return (TextFormat(text));
// }
const char *RL_TextSubtext(const char *text, i32 position, i32 length) // Get a piece of a text string
{
    return (TextSubtext(text, position, length));
}
char *RL_TextReplace(char *text, const char *replace, const char *by) // Replace text string (WARNING: memory must be freed!)
{
    return (TextReplace(text, replace, by));
}
char *RL_TextInsert(const char *text, const char *insert, i32 position) // Insert text in a position (WARNING: memory must be freed!)
{
    return (TextInsert(text, insert, position));
}
const char *RL_TextJoin(const char **textList, i32 count, const char *delimiter) // Join text strings with delimiter
{
    return (TextJoin(textList, count, delimiter));
}
const char **RL_TextSplit(const char *text, char delimiter, i32 *count) // Split text into multiple strings
{
    return (TextSplit(text, delimiter, count));
}
void RL_TextAppend(char *text, const char *append, i32 *position) // Append text at specific position and move cursor!
{
    TextAppend(text, append, position);
}
i32 RL_TextFindIndex(const char *text, const char *find) // Find first text occurrence within a string
{
    return (TextFindIndex(text, find));
}
const char *RL_TextToUpper(const char *text) // Get upper case version of provided string
{
    return (TextToUpper(text));
}
const char *RL_TextToLower(const char *text) // Get lower case version of provided string
{
    return (TextToLower(text));
}
const char *RL_TextToPascal(const char *text) // Get Pascal case notation version of provided string
{
    return (TextToPascal(text));
}
i32 RL_TextToInteger(const char *text) // Get integer value from text (negative values not supported)
{
    return (TextToInteger(text));
}

/***
 * Models
 */
// Basic geometric 3D shapes drawing functions
void RL_DrawLine3D(Vector3 startPos, Vector3 endPos, Color color) // Draw a line in 3D world space
{
    DrawLine3D(startPos, endPos, color);
}
void RL_DrawPoint3D(Vector3 position, Color color) // Draw a point in 3D space, actually a small line
{
    DrawPoint3D(position, color);
}
void RL_DrawCircle3D(Vector3 center, r32 radius, Vector3 rotationAxis, r32 rotationAngle, Color color) // Draw a circle in 3D world space
{
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}
void RL_DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color) // Draw a color-filled triangle (vertex in counter-clockwise order!)
{
    DrawTriangle3D(v1, v2, v3, color);
}
void RL_DrawTriangleStrip3D(Vector3 *points, i32 pointCount, Color color) // Draw a triangle strip defined by points
{
    DrawTriangleStrip3D(points, pointCount, color);
}
void RL_DrawCube(Vector3 position, r32 width, r32 height, r32 length, Color color) // Draw cube
{
    DrawCube(position, width, height, length, color);
}
void RL_DrawCubeV(Vector3 position, Vector3 size, Color color) // Draw cube (Vector version)
{
    DrawCubeV(position, size, color);
}
void RL_DrawCubeWires(Vector3 position, r32 width, r32 height, r32 length, Color color) // Draw cube wires
{
    DrawCubeWires(position, width, height, length, color);
}
void RL_DrawCubeWiresV(Vector3 position, Vector3 size, Color color) // Draw cube wires (Vector version)
{
    DrawCubeWiresV(position, size, color);
}
void RL_DrawCubeTexture(Texture2D texture, Vector3 position, r32 width, r32 height, r32 length, Color color) // Draw cube textured
{
    DrawCubeTexture(texture, position, width, height, length, color);
}
void RL_DrawCubeTextureRec(Texture2D texture, Rec source, Vector3 position, r32 width, r32 height, r32 length, Color color) // Draw cube with a region of a texture
{
    DrawCubeTextureRec(texture, source, position, width, height, length, color);
}
void RL_DrawSphere(Vector3 centerPos, r32 radius, Color color) // Draw sphere
{
    DrawSphere(centerPos, radius, color);
}
void RL_DrawSphereEx(Vector3 centerPos, r32 radius, i32 rings, i32 slices, Color color) // Draw sphere with extended parameters
{
    DrawSphereEx(centerPos, radius, rings, slices, color);
}
void RL_DrawSphereWires(Vector3 centerPos, r32 radius, i32 rings, i32 slices, Color color) // Draw sphere wires
{
    DrawSphereWires(centerPos, radius, rings, slices, color);
}
void RL_DrawCylinder(Vector3 position, r32 radiusTop, r32 radiusBottom, r32 height, i32 slices, Color color) // Draw a cylinder/cone
{
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
}
void RL_DrawCylinderEx(Vector3 startPos, Vector3 endPos, r32 startRadius, r32 endRadius, i32 sides, Color color) // Draw a cylinder with base at startPos and top at endPos
{
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
}
void RL_DrawCylinderWires(Vector3 position, r32 radiusTop, r32 radiusBottom, r32 height, i32 slices, Color color) // Draw a cylinder/cone wires
{
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
}
void RL_DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, r32 startRadius, r32 endRadius, i32 sides, Color color) // Draw a cylinder wires with base at startPos and top at endPos
{
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
}
void RL_DrawPlane(Vector3 centerPos, Vector2 size, Color color) // Draw a plane XZ
{
    DrawPlane(centerPos, size, color);
}
void RL_DrawRay(Ray ray, Color color) // Draw a ray line
{
    DrawRay(ray, color);
}
void RL_DrawGrid(i32 slices, r32 spacing) // Draw a grid (centered at (0, 0, 0))
{
    DrawGrid(slices, spacing);
}

//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Model management functions
Model RL_LoadModel(const char *fileName) // Load model from files (meshes and materials)
{
    return (LoadModel(fileName));
}
Model RL_LoadModelFromMesh(Mesh mesh) // Load model from generated mesh (default material)
{
    return (LoadModelFromMesh(mesh));
}
void RL_UnloadModel(Model model) // Unload model (including meshes) from memory (RAM and/or VRAM)
{
    UnloadModel(model);
}
void RL_UnloadModelKeepMeshes(Model model) // Unload model (but not meshes) from memory (RAM and/or VRAM)
{
    UnloadModelKeepMeshes(model);
}
BoundingBox RL_GetModelBoundingBox(Model model) // Compute model bounding box limits (considers all meshes)
{
    return (GetModelBoundingBox(model));
}

// Model drawing functions
void RL_DrawModel(Model model, Vector3 position, r32 scale, Color tint) // Draw a model (with texture if set)
{
    DrawModel(model, position, scale, tint);
}
void RL_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, r32 rotationAngle, Vector3 scale, Color tint) // Draw a model with extended parameters
{
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
}
void RL_DrawModelWires(Model model, Vector3 position, r32 scale, Color tint) // Draw a model wires (with texture if set)
{
    DrawModelWires(model, position, scale, tint);
}
void RL_DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, r32 rotationAngle, Vector3 scale, Color tint) // Draw a model wires (with texture if set) with extended parameters
{
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
}
void RL_DrawBoundingBox(BoundingBox box, Color color) // Draw bounding box (wires)
{
    DrawBoundingBox(box, color);
}
void RL_DrawBillboard(Camera camera, Texture2D texture, Vector3 position, r32 size, Color tint) // Draw a billboard texture
{
    DrawBillboard(camera, texture, position, size, tint);
}
void RL_DrawBillboardRec(Camera camera, Texture2D texture, Rec source, Vector3 position, Vector2 size, Color tint) // Draw a billboard texture defined by source
{
    DrawBillboardRec(camera, texture, source, position, size, tint);
}
void RL_DrawBillboardPro(Camera camera, Texture2D texture, Rec source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, r32 rotation, Color tint) // Draw a billboard texture defined by source and rotation
{
    DrawBillboardPro(camera, texture, source, position, up, size, origin, rotation, tint);
}

// Mesh management functions
void RL_UploadMesh(Mesh *mesh, b32 dynamic) // Upload mesh vertex data in GPU and provide VAO/VBO ids
{
    UploadMesh(mesh, dynamic);
}
void RL_UpdateMeshBuffer(Mesh mesh, i32 index, const void *data, i32 dataSize, i32 offset) // Update mesh vertex data in GPU for a specific buffer index
{
    UpdateMeshBuffer(mesh, index, data, dataSize, offset);
}
void RL_UnloadMesh(Mesh mesh) // Unload mesh data from CPU and GPU
{
    UnloadMesh(mesh);
}
void RL_DrawMesh(Mesh mesh, Material material, Matrix transform) // Draw a 3d mesh with material and transform
{
    DrawMesh(mesh, material, transform);
}
void RL_DrawMeshInstanced(Mesh mesh, Material material, const Matrix *transforms, i32 instances) // Draw multiple mesh instances with material and different transforms
{
    DrawMeshInstanced(mesh, material, transforms, instances);
}
b32 RL_ExportMesh(Mesh mesh, const char *fileName) // Export mesh data to file, returns true on success
{
    return (ExportMesh(mesh, fileName));
}
BoundingBox RL_GetMeshBoundingBox(Mesh mesh) // Compute mesh bounding box limits
{
    return (GetMeshBoundingBox(mesh));
}
void RL_GenMeshTangents(Mesh *mesh) // Compute mesh tangents
{
    GenMeshTangents(mesh);
}

// Mesh generation functions
Mesh RL_GenMeshPoly(i32 sides, r32 radius) // Generate polygonal mesh
{
    return (GenMeshPoly(sides, radius));
}
Mesh RL_GenMeshPlane(r32 width, r32 length, i32 resX, i32 resZ) // Generate plane mesh (with subdivisions)
{
    return (GenMeshPlane(width, length, resX, resZ));
}
Mesh RL_GenMeshCube(r32 width, r32 height, r32 length) // Generate cuboid mesh
{
    return (GenMeshCube(width, height, length));
}
Mesh RL_GenMeshSphere(r32 radius, i32 rings, i32 slices) // Generate sphere mesh (standard sphere)
{
    return (GenMeshSphere(radius, rings, slices));
}
Mesh RL_GenMeshHemiSphere(r32 radius, i32 rings, i32 slices) // Generate half-sphere mesh (no bottom cap)
{
    return (GenMeshHemiSphere(radius, rings, slices));
}
Mesh RL_GenMeshCylinder(r32 radius, r32 height, i32 slices) // Generate cylinder mesh
{
    return (GenMeshCylinder(radius, height, slices));
}
Mesh RL_GenMeshCone(r32 radius, r32 height, i32 slices) // Generate cone/pyramid mesh
{
    return (GenMeshCone(radius, height, slices));
}
Mesh RL_GenMeshTorus(r32 radius, r32 size, i32 radSeg, i32 sides) // Generate torus mesh
{
    return (GenMeshTorus(radius, size, radSeg, sides));
}
Mesh RL_GenMeshKnot(r32 radius, r32 size, i32 radSeg, i32 sides) // Generate trefoil knot mesh
{
    return (GenMeshKnot(radius, size, radSeg, sides));
}
Mesh RL_GenMeshHeightmap(Image heightmap, Vector3 size) // Generate heightmap mesh from image data
{
    return (GenMeshHeightmap(heightmap, size));
}
Mesh RL_GenMeshCubicmap(Image cubicmap, Vector3 cubeSize) // Generate cubes-based map mesh from image data
{
    return (GenMeshCubicmap(cubicmap, cubeSize));
}

// Material loading/unloading functions
Material *RL_LoadMaterials(const char *fileName, i32 *materialCount) // Load materials from model file
{
    return (LoadMaterials(fileName, materialCount));
}
Material RL_LoadMaterialDefault(void) // Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
{
    return (LoadMaterialDefault());
}
void RL_UnloadMaterial(Material material) // Unload material from GPU memory (VRAM)
{
    UnloadMaterial(material);
}
void RL_SetMaterialTexture(Material *material, i32 mapType, Texture2D texture) // Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
{
    SetMaterialTexture(material, mapType, texture);
}
void RL_SetModelMeshMaterial(Model *model, i32 meshId, i32 materialId) // Set material for a mesh
{
    SetModelMeshMaterial(model, meshId, materialId);
}

// Model animations loading/unloading functions
ModelAnimation *RL_LoadModelAnimations(const char *fileName, u32 *animCount) // Load model animations from file
{
    return (LoadModelAnimations(fileName, animCount));
}
void RL_UpdateModelAnimation(Model model, ModelAnimation anim, i32 frame) // Update model animation pose
{
    UpdateModelAnimation(model, anim, frame);
}
void RL_UnloadModelAnimation(ModelAnimation anim) // Unload animation data
{
    UnloadModelAnimation(anim);
}
void RL_UnloadModelAnimations(ModelAnimation *animations, u32 count) // Unload animation array data
{
    UnloadModelAnimations(animations, count);
}
b32 RL_IsModelAnimationValid(Model model, ModelAnimation anim) // Check model animation skeleton match
{
    return (IsModelAnimationValid(model, anim));
}

// Collision detection functions
b32 RL_CheckCollisionSpheres(Vector3 center1, r32 radius1, Vector3 center2, r32 radius2) // Check collision between two spheres
{
    return (CheckCollisionSpheres(center1, radius1, center2, radius2));
}
b32 RL_CheckCollisionBoxes(BoundingBox box1, BoundingBox box2) // Check collision between two bounding boxes
{
    return (CheckCollisionBoxes(box1, box2));
}
b32 RL_CheckCollisionBoxSphere(BoundingBox box, Vector3 center, r32 radius) // Check collision between box and sphere
{
    return (CheckCollisionBoxSphere(box, center, radius));
}
RayCollision RL_GetRayCollisionSphere(Ray ray, Vector3 center, r32 radius) // Get collision info between ray and sphere
{
    return (GetRayCollisionSphere(ray, center, radius));
}
RayCollision RL_GetRayCollisionBox(Ray ray, BoundingBox box) // Get collision info between ray and box
{
    return (GetRayCollisionBox(ray, box));
}
RayCollision RL_GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform) // Get collision info between ray and mesh
{
    return (GetRayCollisionMesh(ray, mesh, transform));
}
RayCollision RL_GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3) // Get collision info between ray and triangle
{
    return (GetRayCollisionTriangle(ray, p1, p2, p3));
}
RayCollision RL_GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) // Get collision info between ray and quad
{
    return (GetRayCollisionQuad(ray, p1, p2, p3, p4));
}

/***
 * Audio
 */
// Audio device management functions
void RL_InitAudioDevice(void) // Initialize audio device and context
{
    InitAudioDevice();
}
void RL_CloseAudioDevice(void) // Close the audio device and context
{
    CloseAudioDevice();
}
b32 RL_IsAudioDeviceReady(void) // Check if audio device has been initialized successfully
{
    return (IsAudioDeviceReady());
}
void RL_SetMasterVolume(r32 volume) // Set master volume (listener)
{
    SetMasterVolume(volume);
}

// Wave/Sound loading/unloading functions
Wave RL_LoadWave(const char *fileName) // Load wave data from file
{
    return (LoadWave(fileName));
}
Wave RL_LoadWaveFromMemory(const char *fileType, const unsigned char *fileData, i32 dataSize) // Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
{
    return (LoadWaveFromMemory(fileType, fileData, dataSize));
}
Sound RL_LoadSound(const char *fileName) // Load sound from file
{
    return (LoadSound(fileName));
}
Sound RL_LoadSoundFromWave(Wave wave) // Load sound from wave data
{
    return (LoadSoundFromWave(wave));
}
void RL_UpdateSound(Sound sound, const void *data, i32 sampleCount) // Update sound buffer with new data
{
    UpdateSound(sound, data, sampleCount);
}
void RL_UnloadWave(Wave wave) // Unload wave data
{
    UnloadWave(wave);
}
void RL_UnloadSound(Sound sound) // Unload sound
{
    UnloadSound(sound);
}
b32 RL_ExportWave(Wave wave, const char *fileName) // Export wave data to file, returns true on success
{
    return (ExportWave(wave, fileName));
}
b32 RL_ExportWaveAsCode(Wave wave, const char *fileName) // Export wave sample data to code (.h), returns true on success
{
    return (ExportWaveAsCode(wave, fileName));
}

// Wave/Sound management functions
void RL_PlaySound(Sound sound) // Play a sound
{
    PlaySound(sound);
}
void RL_StopSound(Sound sound) // Stop playing a sound
{
    StopSound(sound);
}
void RL_PauseSound(Sound sound) // Pause a sound
{
    PauseSound(sound);
}
void RL_ResumeSound(Sound sound) // Resume a paused sound
{
    ResumeSound(sound);
}
void RL_PlaySoundMulti(Sound sound) // Play a sound (using multichannel buffer pool)
{
    PlaySoundMulti(sound);
}
void RL_StopSoundMulti(void) // Stop any sound playing (using multichannel buffer pool)
{
    StopSoundMulti();
}
i32 RL_GetSoundsPlaying(void) // Get number of sounds playing in the multichannel
{
    return (GetSoundsPlaying());
}
b32 RL_IsSoundPlaying(Sound sound) // Check if a sound is currently playing
{
    return (IsSoundPlaying(sound));
}
void RL_SetSoundVolume(Sound sound, r32 volume) // Set volume for a sound (1.0 is max level)
{
    SetSoundVolume(sound, volume);
}
void RL_SetSoundPitch(Sound sound, r32 pitch) // Set pitch for a sound (1.0 is base level)
{
    SetSoundPitch(sound, pitch);
}
void RL_SetSoundPan(Sound sound, r32 pan) // Set pan for a sound (0.5 is center)
{
    SetSoundPan(sound, pan);
}
Wave RL_WaveCopy(Wave wave) // Copy a wave to a new wave
{
    return (WaveCopy(wave));
}
void RL_WaveCrop(Wave *wave, i32 initSample, i32 finalSample) // Crop a wave to defined samples range
{
    WaveCrop(wave, initSample, finalSample);
}
void RL_WaveFormat(Wave *wave, i32 sampleRate, i32 sampleSize, i32 channels) // Convert wave data to desired format
{
    WaveFormat(wave, sampleRate, sampleSize, channels);
}
r32 *RL_LoadWaveSamples(Wave wave) // Load samples data from wave as a 32bit r32 data array
{
    return (LoadWaveSamples(wave));
}
void RL_UnloadWaveSamples(r32 *samples) // Unload samples data loaded with LoadWaveSamples()
{
    UnloadWaveSamples(samples);
}

// Music management functions
Music RL_LoadMusicStream(const char *fileName) // Load music stream from file
{
    return (LoadMusicStream(fileName));
}
Music RL_LoadMusicStreamFromMemory(const char *fileType, const unsigned char *data, i32 dataSize) // Load music stream from data
{
    return (LoadMusicStreamFromMemory(fileType, data, dataSize));
}
void RL_UnloadMusicStream(Music music) // Unload music stream
{
    UnloadMusicStream(music);
}
void RL_PlayMusicStream(Music music) // Start music playing
{
    PlayMusicStream(music);
}
b32 RL_IsMusicStreamPlaying(Music music) // Check if music is playing
{
    return (IsMusicStreamPlaying(music));
}
void RL_UpdateMusicStream(Music music) // Updates buffers for music streaming
{
    UpdateMusicStream(music);
}
void RL_StopMusicStream(Music music) // Stop music playing
{
    StopMusicStream(music);
}
void RL_PauseMusicStream(Music music) // Pause music playing
{
    PauseMusicStream(music);
}
void RL_ResumeMusicStream(Music music) // Resume playing paused music
{
    ResumeMusicStream(music);
}
void RL_SeekMusicStream(Music music, r32 position) // Seek music to a position (in seconds)
{
    SeekMusicStream(music, position);
}
void RL_SetMusicVolume(Music music, r32 volume) // Set volume for music (1.0 is max level)
{
    SetMusicVolume(music, volume);
}
void RL_SetMusicPitch(Music music, r32 pitch) // Set pitch for a music (1.0 is base level)
{
    SetMusicPitch(music, pitch);
}
void RL_SetMusicPan(Music music, r32 pan) // Set pan for a music (0.5 is center)
{
    SetMusicPan(music, pan);
}
r32 RL_GetMusicTimeLength(Music music) // Get music time length (in seconds)
{
    return (GetMusicTimeLength(music));
}
r32 RL_GetMusicTimePlayed(Music music) // Get current music time played (in seconds)
{
    return (GetMusicTimePlayed(music));
}

// AudioStream management functions
AudioStream RL_LoadAudioStream(u32 sampleRate, u32 sampleSize, u32 channels) // Load audio stream (to stream raw audio pcm data)
{
    return (LoadAudioStream(sampleRate, sampleSize, channels));
}
void RL_UnloadAudioStream(AudioStream stream) // Unload audio stream and free memory
{
    UnloadAudioStream(stream);
}
void RL_UpdateAudioStream(AudioStream stream, const void *data, i32 frameCount) // Update audio stream buffers with data
{
    UpdateAudioStream(stream, data, frameCount);
}
b32 RL_IsAudioStreamProcessed(AudioStream stream) // Check if any audio stream buffers requires refill
{
    return (IsAudioStreamProcessed(stream));
}
void RL_PlayAudioStream(AudioStream stream) // Play audio stream
{
    PlayAudioStream(stream);
}
void RL_PauseAudioStream(AudioStream stream) // Pause audio stream
{
    PauseAudioStream(stream);
}
void RL_ResumeAudioStream(AudioStream stream) // Resume audio stream
{
    ResumeAudioStream(stream);
}
b32 RL_IsAudioStreamPlaying(AudioStream stream) // Check if audio stream is playing
{
    return (IsAudioStreamPlaying(stream));
}
void RL_StopAudioStream(AudioStream stream) // Stop audio stream
{
    StopAudioStream(stream);
}
void RL_SetAudioStreamVolume(AudioStream stream, r32 volume) // Set volume for audio stream (1.0 is max level)
{
    SetAudioStreamVolume(stream, volume);
}
void RL_SetAudioStreamPitch(AudioStream stream, r32 pitch) // Set pitch for audio stream (1.0 is base level)
{
    SetAudioStreamPitch(stream, pitch);
}
void RL_SetAudioStreamPan(AudioStream stream, r32 pan) // Set pan for audio stream (0.5 is centered)
{
    SetAudioStreamPan(stream, pan);
}
void RL_SetAudioStreamBufferSizeDefault(i32 size) // Default size for new audio streams
{
    SetAudioStreamBufferSizeDefault(size);
}
void RL_SetAudioStreamCallback(AudioStream stream, AudioCallback callback) // Audio thread callback to request new data
{
    SetAudioStreamCallback(stream, callback);
}
void RL_AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor) // Attach audio stream processor to stream
{
    AttachAudioStreamProcessor(stream, processor);
}
void RL_DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor) // Detach audio stream processor from stream
{
    DetachAudioStreamProcessor(stream, processor);
}

#if defined(SINGLE_FILE_BUILD)
#else
}
#endif
