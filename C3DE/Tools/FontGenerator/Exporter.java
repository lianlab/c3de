import java.io.*;
import java.nio.ByteBuffer;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
class Exporter 
{
	public static void main(String args[])
	{
		try{
			// Create file 
//			FileWriter fstream = new FileWriter("out.txt");
//			BufferedWriter out = new BufferedWriter(fstream);
			
			FileOutputStream fileOutputStream = new FileOutputStream("out.bin");
			DataOutputStream t_out = new DataOutputStream(fileOutputStream);
			
			
			FileInputStream instream = new FileInputStream("in.txt");
		    // Get the object of DataInputStream
		    DataInputStream in = new DataInputStream(instream);
		        BufferedReader br = new BufferedReader(new InputStreamReader(in));
		    String strLine;
		    //Read File Line By Line
		    
		    String t_str = new String();
		 
		    while ((strLine = br.readLine()) != null)   {
		      // Print the content on the console
//		    	t_str =  t_str.concat("\n" + strLine);
		    	t_str =  t_str.concat(strLine);
		    	
		    	
		    }
		    

		    
		    Pattern patterCharList = Pattern.compile("Define CharList.*?;");
		    Matcher matcherCharList = patterCharList.matcher(t_str);
		    
		    Pattern patternWidthList = Pattern.compile("Define WidthList.*?;");
		    Matcher matcherWidthList = patternWidthList.matcher(t_str);
		    
		    Pattern patternRectList = Pattern.compile("Define RectList.*?;");
		    Matcher matcherRectList = patternRectList.matcher(t_str);
		    
		    Pattern patternOffsetList = Pattern.compile("Define OffsetList.*?;");
		    Matcher matcherOffsetList = patternOffsetList.matcher(t_str);
		    
		    String charList = "";
		    String widthList = "";
		    String rectList = "";
		    String offsetList = "";
		    
		   
		    
		    
		    
		    
		    
		    
		    
		    if(matcherCharList.find())
		    {
		    	charList = matcherCharList.group();		    	
		    }
		    
		    if(matcherWidthList.find())
		    {
		    	widthList = matcherWidthList.group();
		    }
		    
		    if(matcherRectList.find())
		    {
		    	rectList = matcherRectList.group();
		    }
		    
		    if(matcherOffsetList.find())
		    {
		    	offsetList = matcherOffsetList.group();
		    }
		    
		    Pattern patternChars = Pattern.compile("'\\w'");
		    Matcher matcherChars = patternChars.matcher(charList);
		    Vector t_chars = new Vector();
		    while(matcherChars.find())
		    {
		    	char t_char = matcherChars.group().charAt(1);
		    	int t_charInt = (int)t_char;
		    	t_chars.add(t_charInt);
		    }
		    
		    Pattern patternWidths = Pattern.compile("\\d\\d");
		    Matcher matcherWidths = patternWidths.matcher(widthList);
		    Vector t_widths = new Vector();
		    while(matcherWidths.find())
		    {
		    	String t_number = matcherWidths.group();
		    	System.out.println("NUMER : " + t_number);
		    	int t_width = new Integer(t_number);
		    	t_widths.add(t_width);
		    }
		    
		    Pattern patternRects = Pattern.compile("(\\d)+?\\D");
		    Matcher matcherRects = patternRects.matcher(rectList);
		    Vector t_rects = new Vector();
		    while(matcherRects.find())
		    {
		    	String t_number = matcherRects.group();
		    	t_number = t_number.substring(0, t_number.length() - 1);
		    	System.out.println("Rect : " + t_number);
		    	int t_rect = new Integer(t_number);
		    	t_rects.add(t_rect);
		    }
		    
		    Pattern patternOffsets = Pattern.compile("\\-??(\\d)+?\\D");
		    Matcher matcherOffsets = patternOffsets.matcher(offsetList);
		    Vector t_offsets = new Vector();
		    while(matcherOffsets.find())
		    {
		    	String t_offsetString = matcherOffsets.group();
		    	t_offsetString = t_offsetString.substring(0, t_offsetString.length() - 1);
		    	System.out.println("Offset : " + t_offsetString);
		    	int t_offset = new Integer(t_offsetString);
		    	t_offsets.add(t_offset);
		    }
		    
		    System.out.println("here: " + charList);
		    
		    System.out.println("here2: " + widthList);
		    
		    System.out.println("here2: " + rectList);
		    
		    System.out.println("here2: " + offsetList);
		    
		    System.out.println("char :" + (int) 'A');
		    
		    in.close();
		    
		    int totalWrites = 0;
		    
//		    write total of characters
//		    out.write(t_chars.size());
		    t_out.writeInt(swabInt(t_chars.size()));
		    totalWrites++;
//		    write the characters indexes
		    for(int i = 0 ; i < t_chars.size(); i++)
		    {
		    	int charInt = (Integer)t_chars.elementAt(i);
//		    	out.write(charInt);
		    	t_out.writeInt(swabInt(charInt));
		    	totalWrites++;
		    }
		    
//		    writes the widths
		    for(int i = 0 ; i < t_widths.size(); i++)
		    {
		    	int width = (Integer)t_widths.elementAt(i);
//		    	out.write(width);
		    	t_out.writeInt(swabInt(width));
		    	
		    	totalWrites++;
		    }
		    
//		    writes the rects
		    for(int i = 0 ; i < t_rects.size(); i++)
		    {
		    	int rect = (Integer)t_rects.elementAt(i);
//		    	out.write(rect);
		    	t_out.writeInt(swabInt(rect));
		    	totalWrites++;
		    }
		    
//		    writes the offsets
		    for(int i = 0 ; i < t_offsets.size(); i++)
		    {
		    	int offset = (Integer)t_offsets.elementAt(i);
//		    	out.write(offset);
		    	t_out.writeInt(swabInt(offset));
		    	totalWrites++;
		    }
		    
		    t_out.flush();
		    t_out.close();
		    
		    int picles = swabInt(872415232);
			
		    System.out.println("TOTAL: " + totalWrites);
//			out.write("Hello Java");
			//Close the output stream
//			out.close();
		}catch (Exception e){//Catch exception if any
			System.err.println("Error: " + e.getMessage());
		}
	}
	
	public final static int swabInt(int v) {
	     return  (v >>> 24) | (v << 24) | 
	       ((v << 8) & 0x00FF0000) | ((v >> 8) & 0x0000FF00);
	     }

}