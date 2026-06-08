#include "rendering.hpp"

#define WEAK __declspec( selectany )

namespace CodModernWarfare3
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

	WEAK libpsutil::symbol<void*( const char *name, int imageTrack )>R_RegisterFont{ 0x3808B8 };
	WEAK libpsutil::symbol<void*( const char *name, int imageTrack )>Material_RegisterHandle{ 0x38B044 };
	WEAK libpsutil::symbol<ScreenPlacement*( int localClientNum )>ScrPlace_GetActivePlacement{ 0x1174E0 };
	WEAK libpsutil::symbol<void( ScreenPlacement* scrPlace, const char* text, int maxChars, void* font, double x, double y, int horzAlign, int vertAlign, double scale, const float* color, int style )>UI_DrawText{ 0x2522B8 };
	WEAK libpsutil::symbol<void( ScreenPlacement* scrPlace, double x, double y, double w, double h, int horzAlign, int vertAlign, const float* color, void* material )>UI_DrawHandlePic{ 0x23A6B0 };

	void Render( void )
	{
		if( clear_texts )
		{
			clear_texts = false;

			texts.clear();
		}

		if( clear_rects )
		{
			clear_rects = false;

			rects.clear();
		}

		for( int i = 0; i < rects.size(); i++ )
		{
			display_rect* rect = &rects[ i ];
		
			const char* material = rect->material.c_str();

			UI_DrawHandlePic( ScrPlace_GetActivePlacement( rect->localclientnum ), rect->x, rect->y, rect->w, rect->h, 4, 4, rect->color, Material_RegisterHandle( material, 0 ) );
		}

		for( int i = 0; i < texts.size(); i++ )
		{
			display_text* text = &texts[ i ];
		
			const char* str = text->text.c_str();
			const char* font = text->font.c_str();

			UI_DrawText( ScrPlace_GetActivePlacement( text->localclientnum ), str, 0x7FFFFFFF, R_RegisterFont( font, 0 ), text->x, text->y, 4, 4, text->font_size, text->color, 0 );
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
		clear_texts = true;
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
		clear_rects = true;
	}
}