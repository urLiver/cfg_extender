#include "rendering.hpp"

static void* R_RegisterFont( const char *name, int imageTrack )
{
    static libpsutil::symbol<void*( const char *name, int imageTrack )> R_RegisterFont_Ghost{ 0x459C6C };
    static libpsutil::symbol<void*( const char *name, int imageTrack )> R_RegisterFont_Mw3{ 0x3808B8 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return R_RegisterFont_Ghost( name, imageTrack );
        break;
        case Games_Mw3:
            return R_RegisterFont_Mw3( name, imageTrack );
        break;
        default:
            LogWrite( "R_RegisterFont: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

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

static void* ScrPlace_GetActivePlacement( int localClientNum )
{
    static libpsutil::symbol<void*( int localClientNum )> ScrPlace_GetActivePlacement_Ghost{ 0x1B8CCC };
    static libpsutil::symbol<void*( int localClientNum )> ScrPlace_GetActivePlacement_Mw3{ 0x1174E0 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return ScrPlace_GetActivePlacement_Ghost( localClientNum );
        break;
        case Games_Mw3:
            return ScrPlace_GetActivePlacement_Mw3( localClientNum );
        break;
        default:
            LogWrite( "ScrPlace_GetActivePlacement: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

static void UI_DrawText( void* scrPlace, const char* text, int maxChars, void* font, double x, double y, int horzAlign, int vertAlign, double scale, const float* color, int style )
{
    static libpsutil::symbol<void( void* scrPlace, const char* text, int maxChars, void* font, double x, double y, int horzAlign, int vertAlign, double scale, const float* color, int style )> UI_DrawText_Ghost{ 0x348840 };
    static libpsutil::symbol<void( void* scrPlace, const char* text, int maxChars, void* font, double x, double y, int horzAlign, int vertAlign, double scale, const float* color, int style )> UI_DrawText_Mw3{ 0x2522B8 };

    switch( global_current_game )
    {
        case Games_Ghost:
            UI_DrawText_Ghost( scrPlace, text, maxChars, font, x, y, horzAlign, vertAlign, scale, color, style );
        break;
        case Games_Mw3:
            UI_DrawText_Mw3( scrPlace, text, maxChars, font, x, y, horzAlign, vertAlign, scale, color, style );
        break;
        default:
            LogWrite( "UI_DrawText: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static void UI_DrawHandlePic( void* scrPlace, double x, double y, double w, double h, int horzAlign, int vertAlign, const float* color, void* material )
{
    static libpsutil::symbol<void( void* scrPlace, double x, double y, double w, double h, int horzAlign, int vertAlign, const float* color, void* material )> UI_DrawHandlePic_Ghost{ 0x332078 };
    static libpsutil::symbol<void( void* scrPlace, double x, double y, double w, double h, int horzAlign, int vertAlign, const float* color, void* material )> UI_DrawHandlePic_Mw3{ 0x23A6B0 };

    switch( global_current_game )
    {
        case Games_Ghost:
            UI_DrawHandlePic_Ghost( scrPlace, x, y, w, h, horzAlign, vertAlign, color, material );
        break;
        case Games_Mw3:
            UI_DrawHandlePic_Mw3( scrPlace, x, y, w, h, horzAlign, vertAlign, color, material );
        break;
        default:
            LogWrite( "UI_DrawHandlePic: called, but no game case defined for %i", ( int )global_current_game );
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

		UI_DrawHandlePic( ScrPlace_GetActivePlacement( rect->localclientnum ), rect->x, rect->y, rect->w, rect->h, 4, 4, rect->color, Material_RegisterHandle( material, 0 ) );
	}

	for( int i = 0; i < texts.size(); i++ )
	{
		if( clear_texts != -1 && i < clear_texts )
		{
			continue;
		}

		display_text* text = &texts[ i ];
		
		const char* str = text->text.c_str();
		const char* font = text->font.c_str();

		UI_DrawText( ScrPlace_GetActivePlacement( text->localclientnum ), str, 0x7FFFFFFF, R_RegisterFont( font, 0 ), text->x, text->y, 4, 4, text->font_size, text->color, 0 );
	}

	for( int i = 0; i < prints.size(); i++ )
	{
		if( clear_prints != -1 && i < clear_prints )
		{
			continue;
		}

		print* print = &prints[ i ];
		
		const char* str = print->text.c_str();

		static float white[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		UI_DrawText( ScrPlace_GetActivePlacement( print->localclientnum ), str, 0x7FFFFFFF, UI_GetFontHandle( print->font_size, print->font ), print->x, print->y, 4, 4, print->font_size, white, 0 );
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

	if( clear_prints != -1 )
	{
		prints.erase( prints.begin(), prints.begin() + clear_prints );
		
		clear_prints = -1;
	}
}

void AddText( int localclientnum, const char* text, int x, int y, const char* font, float font_size, float r, float g, float b, float a )
{
	display_text new_text;
	new_text.text = std::string( text );
	new_text.x = x;
	new_text.y = y;
	new_text.font = std::string( font );
	new_text.font_size = font_size;
	new_text.color[ 0 ] = r;
	new_text.color[ 1 ] = g;
	new_text.color[ 2 ] = b;
	new_text.color[ 3 ] = a;
	new_text.localclientnum = localclientnum;

	texts.push_back( new_text );
}

void ClearTexts( void )
{
	clear_texts = texts.size();
}

void AddRect( int localclientnum, int x, int y, int w, int h, const char* material, float r, float g, float b, float a )
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
	new_rect.localclientnum = localclientnum;

	rects.push_back( new_rect );
}

void ClearRects( void )
{
	clear_rects = rects.size();
}

void Print( int localclientnum, const char* text )
{
	print new_print;
	new_print.localclientnum = localclientnum;
	new_print.text = std::string( text );
	new_print.x = Dvar_GetInt( "cfge_print_x" );
	new_print.font = Dvar_GetInt( "cfge_print_font" );
	new_print.font_size = Dvar_GetFloat( "cfge_print_size" );
	
	if( print_y == -1 )
	{
		new_print.y = Dvar_GetInt( "cfge_print_y" );
			
		print_y = new_print.y;
	}
	else
	{
		new_print.y = print_y;
	}

	print_y += Dvar_GetInt( "cfge_print_padding" );

	WebmanNotify( va( "%i", new_print.font ) );

	prints.push_back( new_print );
}

void ClearPrints( void )
{
	print_y = -1;

	clear_prints = prints.size();
}
