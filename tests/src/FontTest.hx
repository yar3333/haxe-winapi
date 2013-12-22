package;

import neko.winapi.Font;

class FontTest extends haxe.unit.TestCase
{
    public function testBasic()
    {
		var faces = Font.getFaces();
		
		for (face in faces)
		{
			var styles = Font.getStyles(face);
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
