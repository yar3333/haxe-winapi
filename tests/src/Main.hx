class Main
{
    static function main()
	{
		var r = new haxe.unit.TestRunner();
		r.add(new FontsTest());
		r.add(new RegistryTest());
		r.run();
	}
}
