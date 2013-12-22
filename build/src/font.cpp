#pragma GCC diagnostic ignored "-fpermissive"

#include <windows.h>
#include <neko.h>
#include <stdio.h>

// ========================================================================================

struct FontFaces
{
	int count;
	value *data;
};

struct FontStyles
{
	BOOL regular;
	BOOL italic;
	BOOL bold;
	BOOL boldItalic;
};

BOOL CALLBACK enumFontFamProc_get_faces(LPENUMLOGFONT lpelf, LPNEWTEXTMETRIC lpntm, DWORD FontType, FontFaces *pFontFaces);
BOOL CALLBACK enumFontFamProc_get_styles(LPENUMLOGFONT lpelf, LPNEWTEXTMETRIC lpntm, DWORD FontType, FontStyles *pFontStyles);

value fontStylesToValue(FontStyles *styles);
value arrayToValue(int count, value data[]);
void val_array_set_i(value array, int n, value val);
//size_t strlcpy(char *dst, const char *src, size_t siz);

// ========================================================================================

value get_faces()
{
    FontFaces faces;
	faces.count = 0;
	faces.data = malloc(0);
	EnumFontFamilies(GetDC(NULL), NULL, (FONTENUMPROC)enumFontFamProc_get_faces, (LPARAM)&faces); 
	return arrayToValue(faces.count, faces.data);
}
DEFINE_PRIM(get_faces, 0);

value get_styles(value faceName)
{
    FontStyles styles; 
    styles.regular = FALSE;
    styles.italic = FALSE;
    styles.bold = FALSE;
    styles.boldItalic = FALSE;
	EnumFontFamilies(GetDC(NULL), val_string(faceName), (FONTENUMPROC)enumFontFamProc_get_styles, (LPARAM)&styles); 
	return fontStylesToValue(&styles);
}
DEFINE_PRIM(get_styles, 1);

// ========================================================================================

BOOL CALLBACK enumFontFamProc_get_faces(LPENUMLOGFONT lpelf, LPNEWTEXTMETRIC lpntm, DWORD fontType, FontFaces *pFontFaces)
{ 
	if (lpelf->elfLogFont.lfFaceName[0] != '@')
	{
		pFontFaces->data = realloc(pFontFaces->data, (pFontFaces->count + 1) * sizeof(pFontFaces->data[0]));
		pFontFaces->data[pFontFaces->count] = alloc_string(lpelf->elfLogFont.lfFaceName);
		pFontFaces->count++;
	}
	return TRUE;
} 

BOOL CALLBACK enumFontFamProc_get_styles(LPENUMLOGFONT lpelf, LPNEWTEXTMETRIC lpntm, DWORD fontType, FontStyles *pFontStyles)
{ 
	if (lpelf->elfLogFont.lfWeight >= 700 && lpelf->elfLogFont.lfItalic)
	{
		pFontStyles->boldItalic = TRUE;
	}
	else
	if (lpelf->elfLogFont.lfWeight >= 700)
	{
		pFontStyles->bold = TRUE;
	}
	else
	if (lpelf->elfLogFont.lfItalic)
	{
		pFontStyles->italic = TRUE;
	}
	else
	{
		pFontStyles->regular = TRUE;
	}
		
	return TRUE;
} 

// ========================================================================================

value fontStylesToValue(FontStyles *styles)
{
	value r = alloc_object(NULL);
	alloc_field(r, val_id("regular"), alloc_bool(styles->regular));
	alloc_field(r, val_id("italic"), alloc_bool(styles->italic));
	alloc_field(r, val_id("bold"), alloc_bool(styles->bold));
	alloc_field(r, val_id("boldItalic"), alloc_bool(styles->boldItalic));
	return r;
}

value arrayToValue(int count, value data[])
{
	value r = alloc_array(count);
	for (int i=0; i<count; i++)
	{
		val_array_set_i(r, i, data[i]);
	}
	return r;
}

void val_array_set_i(value array, int n, value val)
{
	if (!val_is_array(array))
	{
		array = val_field(array, val_id("__a"));
	}
	val_array_ptr(array)[n] = val;
}

/*
size_t strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0') break;
		}
	}

	if (n == 0)
	{
		if (siz != 0) *d = '\0';
		while (*s++);
	}

	return s - src - 1;
}
*/
