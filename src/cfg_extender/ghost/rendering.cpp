#include "rendering.hpp"

#define WEAK __declspec( selectany )

namespace CodGhost
{

	struct ScreenPlacement
	{
		float scaleVirtualToReal[2];
		float scaleVirtualToFull[2];
		float scaleRealToVirtual[2];
		float realViewportPosition[2];
		float realViewportSize[2];
		float virtualViewableMin[2];
		float virtualViewableMax[2];
		float realViewableMin[2];
		float realViewableMax[2];
		float virtualAdjustableMin[2];
		float virtualAdjustableMax[2];
		float realAdjustableMin[2];
		float realAdjustableMax[2];
		float subScreenLeft;
	};
	
	WEAK libpsutil::symbol<void*( const char *name, int imageTrack )>R_RegisterFont{ 0x459C6C };
	WEAK libpsutil::symbol<void*( double size, int font )>UI_GetFontHandle{ 0x348DD0 };
	WEAK libpsutil::symbol<void*( const char *name, int imageTrack )>Material_RegisterHandle{ 0x46540C };
	WEAK libpsutil::symbol<ScreenPlacement*( int localClientNum )>ScrPlace_GetActivePlacement{ 0x1B8CCC };
	WEAK libpsutil::symbol<void( ScreenPlacement* scrPlace, const char* text, int maxChars, void* font, double x, double y, int horzAlign, int vertAlign, double scale, const float* color, int style )>UI_DrawText{ 0x348840 };
	WEAK libpsutil::symbol<void( ScreenPlacement* scrPlace, double x, double y, double w, double h, int horzAlign, int vertAlign, const float* color, void* material )>UI_DrawHandlePic{ 0x332078 };
	
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
}