package;

import neko.winapi.Fonts;

class FontsTest extends haxe.unit.TestCase
{
    public function testBasic()
    {
		var faces = Fonts.getFaces();
		
		for (face in faces)
		{
			var styles = Fonts.getStyles(face);
			print(face + "\n");
			print(
				"\t" 
				+ (styles.regular ? " regular" : "")
				+ (styles.italic ? " italic" : "")
				+ (styles.bold ? " bold" : "")
				+ (styles.boldItalic ? " boldItalic" : "")
				+ "\n"
			);
		}
		
		this.assertTrue(true);
    }
}
