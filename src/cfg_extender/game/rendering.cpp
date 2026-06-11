#include "rendering.hpp"

static void* UI_GetFontHandle( double size, int font )
{
    static libpsutil::symbol<void*( double size, int font )> UI_GetFontHandle_Ghost{ 0x348DD0 };
    static libpsutil::symbol<void*( double size, int font )> UI_GetFontHandle_Mw3{ 0x252848 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return UI_GetFontHandle_Ghost( size, font );
        break;
        case Games_Mw3:
            return UI_GetFontHandle_Mw3( size, font );
        break;
        default:
            LogWrite( "UI_GetFontHandle: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

static void* Material_RegisterHandle( const char *name, int imageTrack )
{
    static libpsutil::symbol<void*( const char *name, int imageTrack )> Material_RegisterHandle_Ghost{ 0x46540C };
    static libpsutil::symbol<void*( const char *name, int imageTrack )> Material_RegisterHandle_Mw3{ 0x38B044 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Material_RegisterHandle_Ghost( name, imageTrack );
        break;
        case Games_Mw3:
            return Material_RegisterHandle_Mw3( name, imageTrack );
        break;
        default:
            LogWrite( "Material_RegisterHandle: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

static void R_AddCmdDrawText( const char* text, void* font, double x, double y, double scale, const float* color )
{
    static libpsutil::symbol<void( const char *text, int maxChars, void *font, double x, double y, double xScale, double yScale, double rotation, const float *color, int style )> R_AddCmdDrawText_Ghost{ 0x473658 };
    static libpsutil::symbol<void( const char *text, int maxChars, void *font, double x, double y, double xScale, double yScale, double rotation, const float *color, int style )> R_AddCmdDrawText_Mw3{ 0x393640 };

    switch( global_current_game )
    {
        case Games_Ghost:
            R_AddCmdDrawText_Ghost( text, 0x7FFFFFFF, font, x, y, scale, scale, 0, color, 0 );
        break;
        case Games_Mw3:
            R_AddCmdDrawText_Mw3( text, 0x7FFFFFFF, font, x, y, scale, scale, 0, color, 0 );
        break;
        default:
            LogWrite( "R_AddCmdDrawText: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static void R_AddCmdDrawStretchPic( double x, double y, double w, double h, const float* color, void* material )
{
    static libpsutil::symbol<void( float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, void *material )> R_AddCmdDrawStretchPic_Ghost{ 0x332078 };
    static libpsutil::symbol<void( float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, void *material )> R_AddCmdDrawStretchPic_Mw3{ 0x392D78 };

    switch( global_current_game )
    {
        case Games_Ghost:
            R_AddCmdDrawStretchPic_Ghost( x, y, w, h, 1, 1, 1, 1, color, material );
        break;
        case Games_Mw3:
            R_AddCmdDrawStretchPic_Mw3( x, y, w, h, 1, 1, 1, 1, color, material );
        break;
        default:
            LogWrite( "R_AddCmdDrawStretchPic: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

void Render( void )
{
	for( int i = 0; i < rects.size(); i++ )
	{
		if( clear_rects != -1 && i < clear_rects )
		{
			continue;
		}

		display_rect* rect = &rects[ i ];
		
		const char* material = rect->material.c_str();

		R_AddCmdDrawStretchPic( rect->x, rect->y, rect->w, rect->h, rect->color, Material_RegisterHandle( material, 0 ) );
	}

	for( int i = 0; i < texts.size(); i++ )
	{
		if( clear_texts != -1 && i < clear_texts )
		{
			continue;
		}

		display_text* text = &texts[ i ];
		
		const char* str = text->text.c_str();
		
		R_AddCmdDrawText( str, UI_GetFontHandle( text->font_size, text->font ), text->x, text->y, text->font_size, text->color );
	}
		
	if( clear_texts != -1 )
	{
		texts.erase( texts.begin(), texts.begin() + clear_texts );

		clear_texts = -1;
	}

	if( clear_rects != -1 )
	{
		rects.erase( rects.begin(), rects.begin() + clear_rects );
		
		clear_rects = -1;
	}
}

void AddText( const char* text, int x, int y, int font, float font_size, float r, float g, float b, float a )
{
	display_text new_text;
	new_text.text = std::string( text );
	new_text.x = x;
	new_text.y = y;
	new_text.font = font;
	new_text.font_size = font_size;
	new_text.color[ 0 ] = r;
	new_text.color[ 1 ] = g;
	new_text.color[ 2 ] = b;
	new_text.color[ 3 ] = a;

	texts.push_back( new_text );
}

void ClearTexts( void )
{
	clear_texts = texts.size();
}

void AddRect( int x, int y, int w, int h, const char* material, float r, float g, float b, float a )
{
	display_rect new_rect;
	new_rect.x = x;
	new_rect.y = y;
	new_rect.w = w;
	new_rect.h = h;
	new_rect.material = std::string( material );
	new_rect.color[ 0 ] = r;
	new_rect.color[ 1 ] = g;
	new_rect.color[ 2 ] = b;
	new_rect.color[ 3 ] = a;

	rects.push_back( new_rect );
}

void ClearRects( void )
{
	clear_rects = rects.size();
}