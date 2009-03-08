<?php
	$handle = fopen("../../Runtime/replay.bin", "rb");
	
	
	
	
	if(is_file("../../Runtime/replay.txt"))
	{
		
		unlink("../../Runtime/replay.txt");
	}
	
	$filesize = filesize("../../Runtime/replay.bin");
	$pointer = 0;
	
	$t_out = "";
	
	$tt = 0;
	
	$t_picles = 0;
	//while (!feof($handle)) 
	while ($t_picles < $filesize) 
	{
		$picles = (int)fread($handle, 4);
		var_dump($picles);
		$t_picles += 4;
		$tt++;
		/*
		$t_out .= "FPS: ";
		$t_out .= fread($handle, 4);
		
		$t_out .= "; Key 1: ";
		$t_out .= fread($handle, 4);
		$t_out .= "; Key 2: ";
		$t_out .= fread($handle, 4);
		$t_out .= "; Key 3: ";
		$t_out .= fread($handle, 4);
		$t_out .= "; Key 4: ";
		$t_out .= fread($handle, 4);
		$t_out .= "\n";
		
	   $tt++;
		*/
		//echo $picles;
	}
	
	echo PHP_INT_MAX;
	
	echo "\n" . $filesize;
	
	
	
	
	$handle2 = fopen("../../Runtime/replay.txt", "w");
	fwrite($handle2, $t_out);
	fclose($handle2);
	fclose($handle);
?>