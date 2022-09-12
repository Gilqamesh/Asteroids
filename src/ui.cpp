internal inline
void ConfigureButton( RenderTexture2D *RenderTexture, button *Button, const char *text, Font font, r32 FontSize, Color ContentColor, Color BorderColor, Color HighlightColor,
    Vector2 MarginSize, Vector2 BorderSize, Vector2 PaddingSize, u32 ButtonType, u32 MaxButtons, Vector2 MousePosition)
{
    Button->Text = text;
    Button->font = font;
    Button->FontSize = FontSize;
    if (RecVsPoint(MousePosition, Button->ContentBound))
    {
        Button->IsHighlighted = true;
        Button->ContentColor = HighlightColor;
    }
    else
    {
        Button->IsHighlighted = false;
        Button->ContentColor = ContentColor;
    }
    Button->BorderColor = BorderColor;
    Button->MarginSize = MarginSize;
    Button->BorderSize = BorderSize;
    Button->PaddingSize = PaddingSize;
    Button->ContentSize = { (r32)RenderTexture->texture.width / 2.0f, (r32)RenderTexture->texture.height / 10.0f };
    Button->Content = { (r32)RenderTexture->texture.width / 2.0f - Button->ContentSize.x / 2.0f,
                        (r32)((ButtonType + 1) * RenderTexture->texture.height) / (r32)(MaxButtons + 1) };
    Button->ContentBound = { Button->Content.x, Button->Content.y, Button->ContentSize.x, Button->ContentSize.y };
}

internal inline void
DrawButton(raylib_wrapper_code *RL, button *Button, r32 Spacing)
{
    // void DrawRectangleLines(int posX, int posY, int width, int height, Color color);
    // Draw Margin
    // RL->DrawRectangle((i32)round(Button->Content.x - Button->PaddingSize.x - Button->BorderSize.x - Button->MarginSize.x),
    //                     (i32)round(Button->Content.y - Button->PaddingSize.y - Button->BorderSize.y - Button->MarginSize.y),
    //                     (i32)round(Button->ContentSize.x + 2.0f * Button->MarginSize.x + 2.0f * Button->BorderSize.x + 2.0f * Button->PaddingSize.x),
    //                     (i32)round(Button->ContentSize.y + 2.0f * Button->MarginSize.y + 2.0f * Button->BorderSize.y + 2.0f * Button->PaddingSize.y),
    //                     GRAY);
    // Draw Border
    RL->DrawRectangle((i32)round(Button->Content.x - Button->PaddingSize.x - Button->BorderSize.x),
                      (i32)round(Button->Content.y - Button->PaddingSize.y - Button->BorderSize.y),
                      (i32)round(Button->ContentSize.x + 2.0f * Button->BorderSize.x + 2.0f * Button->PaddingSize.x),
                      (i32)round(Button->ContentSize.y + 2.0f * Button->BorderSize.y + 2.0f * Button->PaddingSize.y),
                      Button->BorderColor);
    // Draw Padding
    // RL->DrawRectangle((i32)round(Button->Content.x - Button->PaddingSize.x),
    //                     (i32)round(Button->Content.y - Button->PaddingSize.y),
    //                     (i32)round(Button->ContentSize.x + 2.0f * Button->PaddingSize.x),
    //                     (i32)round(Button->ContentSize.y + 2.0f * Button->PaddingSize.y),
    //                     RED);
    // Draw Content
    RL->DrawRectangle((i32)round(Button->Content.x),
                      (i32)round(Button->Content.y),
                      (i32)round(Button->ContentSize.x),
                      (i32)round(Button->ContentSize.y),
                      WHITE);
    Vector2 TextSize = RL->MeasureTextEx(Button->font, Button->Text, Button->FontSize, Spacing);
    r32 OffsetX = (Button->ContentSize.x - TextSize.x) / 2.0f;
    RL->RL_DrawTextEx(Button->font, Button->Text, { Button->Content.x + OffsetX, Button->Content.y + Button->ContentSize.y / 2.0f - Button->FontSize / 2.0f},
        Button->FontSize, Spacing, Button->ContentColor);
}

internal inline void
PutText(game_state *GameState, raylib_wrapper_code *RL, const char *Text, Vector2 Position,
    r32 FontSize, Color color, r32 Spacing = 1.0f)
{
    Vector2 TextSize = RL->MeasureTextEx(GameState->Fonts[0], Text, FontSize, Spacing);
    RL->RL_DrawText(Text, (i32)(Position.x - TextSize.x / 2.0f), (i32)(Position.y - TextSize.y / 2.0f),
        FontSize, color);
}
