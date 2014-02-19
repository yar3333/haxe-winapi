package neko.winapi;

import neko.Lib;

typedef FontStyles =
{
	var regular : Bool;
	var italic : Bool;
	var bold : Bool;
	var boldItalic : Bool;
}

class Fonts
{
	public static function getFaces() : Array<String>
	{
		return Lib.nekoToHaxe(get_faces());
	}
	
	public static function getStyles(faceName:String) : FontStyles
	{
		return Lib.nekoToHaxe(get_styles(Lib.haxeToNeko(faceName)));
	}
	
	static var get_faces = Lib.loadLazy("winapi","get_faces", 0);
	static var get_styles = Lib.loadLazy("winapi","get_styles", 1);
}
