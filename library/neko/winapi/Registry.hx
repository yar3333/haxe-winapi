package neko.winapi;

import neko.Lib;

abstract HKEY(Int)
{
	inline public function new(i:Int) this = i;
}

class Registry
{
	public static var HKEY_CLASSES_ROOT(default, null) = new HKEY(0x80000000);
	public static var HKEY_CURRENT_USER(default, null) = new HKEY(0x80000001);
	public static var HKEY_LOCAL_MACHINE(default, null) = new HKEY(0x80000002);
	public static var HKEY_USERS(default, null) = new HKEY(0x80000003);
	public static var HKEY_PERFORMANCE_DATA(default, null) = new HKEY(0x80000004);
	public static var HKEY_CURRENT_CONFIG(default, null) = new HKEY(0x80000005);
	public static var HKEY_DYN_DATA(default, null) = new HKEY(0x80000006);
	
	public static function createKey(globalKey:HKEY, name:String) : Bool
	{
		return Lib.nekoToHaxe(registry_createKey(globalKey, Lib.haxeToNeko(name)));
	}
	
	public static function getKeyValueString(globalKey:HKEY, path:String, name:String) : String
	{
		return Lib.nekoToHaxe(registry_getKeyValueStr(globalKey, Lib.haxeToNeko(path), Lib.haxeToNeko(name)));
	}
	
	public static function setKeyValueString(globalKey:HKEY, path:String, name:String, value:String) : Bool
	{
		return Lib.nekoToHaxe(registry_setKeyValueStr(globalKey, Lib.haxeToNeko(path), Lib.haxeToNeko(name), Lib.haxeToNeko(value)));
	}
	
	static var registry_createKey = Lib.loadLazy("winapi","registry_createKey", 2);
	static var registry_getKeyValueStr = Lib.loadLazy("winapi","registry_getKeyValueStr", 3);
	static var registry_setKeyValueStr = Lib.loadLazy("winapi","registry_setKeyValueStr", 4);
}
