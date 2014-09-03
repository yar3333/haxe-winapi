#include <windows.h>
#include <neko.h>
#include <stdio.h>

#define REGKEY(o) (HKEY)val_int32(o)

value registry_createKey(value hKey, value keyName)
{
	val_check(hKey, int32);
	val_check(keyName, string);
	
	HKEY hResKey;
	if (RegCreateKey(REGKEY(hKey), val_string(keyName), &hResKey) == ERROR_SUCCESS)
	{
		RegCloseKey(hResKey);
		return val_true;
	}
	
	return val_false;
}
DEFINE_PRIM(registry_createKey, 2);

value registry_getKeyValueStr(value _globalKey, value _pathToKey, value _keyName)
{
	val_check(_globalKey, int32);
	val_check(_pathToKey, string);
	val_check(_keyName, string);
	
	HKEY hKey; 
	if (RegOpenKeyEx(REGKEY(_globalKey), val_string(_pathToKey), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) return val_null;

	char bufStr[1024] = "";
	DWORD bufSize = sizeof(bufStr);
	RegQueryValueEx(hKey, val_string(_keyName), NULL, NULL, (LPBYTE)bufStr, &bufSize);
	
	RegCloseKey(hKey);

	return alloc_string(bufStr);
}
DEFINE_PRIM(registry_getKeyValueStr, 3);

value registry_setKeyValueStr(value globalKey, value pathToKey, value keyName, value keyVal)
{
	val_check(globalKey, int32);
	val_check(pathToKey, string);
	val_check(keyName, string);
	val_check(keyVal, string);
	
	HKEY hKey; 
	if (RegCreateKey(REGKEY(globalKey), val_string(pathToKey), &hKey) != ERROR_SUCCESS) return val_false;
	
	if (RegSetValue(hKey, val_string(keyName), REG_SZ, val_string(keyVal), val_strlen(keyVal) + 1) == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return val_true;
	}

	RegCloseKey(hKey);
	return val_false;
}
DEFINE_PRIM(registry_setKeyValueStr, 4);
