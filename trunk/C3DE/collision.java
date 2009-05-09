
	
	
	private static float[] mBox1X;
	private static float[] mBox1Y;
	private static float[] mBox2X;
	private static float[] mBox2Y;
	
	private static float mBox1PosX;
	private static float mBox1PosY;
	private static float mBox2PosX;
	private static float mBox2PosY;
	
	private static float mBox1Rotation;
	private static float mBox2Rotation;
	
	private static boolean switchHack = true;
	
	private static void drawHackBoxes(Graphics g)
	{	
		
		float tBox10X = ((float)Math.cos(mBox1Rotation))*mBox1X[0] + (mBox1Y[0]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox10Y = (float)Math.sin(mBox1Rotation)*mBox1X[0] + (mBox1Y[0]*((float)Math.cos(mBox1Rotation)));
		float tBox11X = ((float)Math.cos(mBox1Rotation))*mBox1X[1] + (mBox1Y[1]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox11Y = (float)Math.sin(mBox1Rotation)*mBox1X[1] + (mBox1Y[1]*((float)Math.cos(mBox1Rotation)));
		float tBox12X = ((float)Math.cos(mBox1Rotation))*mBox1X[2] + (mBox1Y[2]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox12Y = (float)Math.sin(mBox1Rotation)*mBox1X[2] + (mBox1Y[2]*((float)Math.cos(mBox1Rotation)));
		float tBox13X = ((float)Math.cos(mBox1Rotation))*mBox1X[3] + (mBox1Y[3]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox13Y = (float)Math.sin(mBox1Rotation)*mBox1X[3] + (mBox1Y[3]*((float)Math.cos(mBox1Rotation)));
		
		tBox10X += mBox1PosX;
		tBox10Y += mBox1PosY;
		tBox11X += mBox1PosX;
		tBox11Y += mBox1PosY;
		tBox12X += mBox1PosX;
		tBox12Y += mBox1PosY;
		tBox13X += mBox1PosX;
		tBox13Y += mBox1PosY;
		
		float tBox20X = ((float)Math.cos(mBox2Rotation))*mBox2X[0] + (mBox2Y[0]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox20Y = (float)Math.sin(mBox2Rotation)*mBox2X[0] + (mBox2Y[0]*((float)Math.cos(mBox2Rotation)));
		float tBox21X = ((float)Math.cos(mBox2Rotation))*mBox2X[1] + (mBox2Y[1]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox21Y = (float)Math.sin(mBox2Rotation)*mBox2X[1] + (mBox2Y[1]*((float)Math.cos(mBox2Rotation)));
		float tBox22X = ((float)Math.cos(mBox2Rotation))*mBox2X[2] + (mBox2Y[2]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox22Y = (float)Math.sin(mBox2Rotation)*mBox2X[2] + (mBox2Y[2]*((float)Math.cos(mBox2Rotation)));
		float tBox23X = ((float)Math.cos(mBox2Rotation))*mBox2X[3] + (mBox2Y[3]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox23Y = (float)Math.sin(mBox2Rotation)*mBox2X[3] + (mBox2Y[3]*((float)Math.cos(mBox2Rotation)));
		
		tBox20X += mBox2PosX;
		tBox20Y += mBox2PosY;
		tBox21X += mBox2PosX;
		tBox21Y += mBox2PosY;
		tBox22X += mBox2PosX;
		tBox22Y += mBox2PosY;
		tBox23X += mBox2PosX;
		tBox23Y += mBox2PosY;

		g.setColor(0xff0000);
		
		g.drawLine((int)tBox10X, (int)tBox10Y, (int)tBox11X, (int)tBox11Y);
		g.drawLine((int)tBox10X, (int)tBox10Y, (int)tBox12X, (int)tBox12Y);
		g.drawLine((int)tBox12X, (int)tBox12Y, (int)tBox13X, (int)tBox13Y);
		g.drawLine((int)tBox13X, (int)tBox13Y, (int)tBox11X, (int)tBox11Y);
		
		
		g.setColor(0x00ff00);
		
		g.drawLine((int)tBox20X, (int)tBox20Y, (int)tBox21X, (int)tBox21Y);
		g.drawLine((int)tBox20X, (int)tBox20Y, (int)tBox22X, (int)tBox22Y);
		g.drawLine((int)tBox22X, (int)tBox22Y, (int)tBox23X, (int)tBox23Y);
		g.drawLine((int)tBox23X, (int)tBox23Y, (int)tBox21X, (int)tBox21Y);
		
		if(boxesCollides(g))
		{
			System.out.println("COLLSION!!");
		}
		
	}
	
	private static void initHackBoxes()
	{
		mBox1X = new float[4];
		mBox1Y = new float[4];
		mBox2X = new float[4];
		mBox2Y = new float[4];
		
		mBox1X[0] = -50.0f;
		mBox1X[1] = 50.0f;
		mBox1X[2] = -50.0f;
		mBox1X[3] = 50.0f;
		
		mBox1Y[0] = -50.0f;
		mBox1Y[1] = -50.0f;
		mBox1Y[2] = 50.0f;
		mBox1Y[3] = 50.0f;
		
		mBox2X[0] = -50.0f;
		mBox2X[1] = 50.0f;
		mBox2X[2] = -50.0f;
		mBox2X[3] = 50.0f;
		
		mBox2Y[0] = -50.0f;
		mBox2Y[1] = -50.0f;
		mBox2Y[2] = 50.0f;
		mBox2Y[3] = 50.0f;
		
		mBox1PosX = 150.0f;
		mBox1PosY = 150.0f;
		
		mBox2PosX = 300.0f;
		mBox2PosY = 150.0f;
		
		mBox1Rotation = 0.0f;
		mBox2Rotation = 0.0f;
		
	}
	
	private static float mStep = 1.0f;
	private static boolean switchHack2 = true;
	
	private static void hackInput(int keyCode, int aEventType)
	{
		mStep = (switchHack2)? 1.0f : 8.0f;
		float step = mStep;
		float step2 = 0.1f;
		if(aEventType == Toolkit.EVENT_KEY_PRESSED || aEventType == Toolkit.EVENT_SOFT_KEY_PRESSED)
		{
			switch (keyCode)
			{
			case -2:
				if(switchHack)
				{
					mBox1PosY += step;
				}
				else
				{
					mBox2PosY += step;
				}
				
				break;
				
			case -1:
				if(switchHack)
				{
					mBox1PosY -= step;
				}
				else
				{
					mBox2PosY -= step;
				}
				
				break;
			
			case -3:
				if(switchHack)
				{
					mBox1PosX -= step;
				}
				else
				{
					mBox2PosX -= step;
				}
				
				break;
				
			case -4:
				if(switchHack)
				{
					mBox1PosX += step;
				}
				else
				{
					mBox2PosX += step;
				}
				
				break;
				
			case 42:
				if(switchHack)
				{
					mBox1Rotation += step2;
				}
				else
				{
					mBox2Rotation += step2;
				}
				
				break;
				
			case 35:
				if(switchHack)
				{
					mBox1Rotation -= step2;
				}
				else
				{
					mBox2Rotation -= step2;
				}
				
				break;
				
			case -5:
//				switchHack = !switchHack;
				switchHack2 = !switchHack2;
				
				break;
			}
		}
	}
	
	private static boolean boxesCollides(Graphics g)
	{
		float tBox10X = ((float)Math.cos(mBox1Rotation))*mBox1X[0] + (mBox1Y[0]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox10Y = (float)Math.sin(mBox1Rotation)*mBox1X[0] + (mBox1Y[0]*((float)Math.cos(mBox1Rotation)));
		float tBox11X = ((float)Math.cos(mBox1Rotation))*mBox1X[1] + (mBox1Y[1]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox11Y = (float)Math.sin(mBox1Rotation)*mBox1X[1] + (mBox1Y[1]*((float)Math.cos(mBox1Rotation)));
		float tBox12X = ((float)Math.cos(mBox1Rotation))*mBox1X[2] + (mBox1Y[2]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox12Y = (float)Math.sin(mBox1Rotation)*mBox1X[2] + (mBox1Y[2]*((float)Math.cos(mBox1Rotation)));
		float tBox13X = ((float)Math.cos(mBox1Rotation))*mBox1X[3] + (mBox1Y[3]*(-(float)Math.sin(mBox1Rotation)));		
		float tBox13Y = (float)Math.sin(mBox1Rotation)*mBox1X[3] + (mBox1Y[3]*((float)Math.cos(mBox1Rotation)));
		
		tBox10X += mBox1PosX;
		tBox10Y += mBox1PosY;
		tBox11X += mBox1PosX;
		tBox11Y += mBox1PosY;
		tBox12X += mBox1PosX;
		tBox12Y += mBox1PosY;
		tBox13X += mBox1PosX;
		tBox13Y += mBox1PosY;
		
		float tBox20X = ((float)Math.cos(mBox2Rotation))*mBox2X[0] + (mBox2Y[0]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox20Y = (float)Math.sin(mBox2Rotation)*mBox2X[0] + (mBox2Y[0]*((float)Math.cos(mBox2Rotation)));
		float tBox21X = ((float)Math.cos(mBox2Rotation))*mBox2X[1] + (mBox2Y[1]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox21Y = (float)Math.sin(mBox2Rotation)*mBox2X[1] + (mBox2Y[1]*((float)Math.cos(mBox2Rotation)));
		float tBox22X = ((float)Math.cos(mBox2Rotation))*mBox2X[2] + (mBox2Y[2]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox22Y = (float)Math.sin(mBox2Rotation)*mBox2X[2] + (mBox2Y[2]*((float)Math.cos(mBox2Rotation)));
		float tBox23X = ((float)Math.cos(mBox2Rotation))*mBox2X[3] + (mBox2Y[3]*(-(float)Math.sin(mBox2Rotation)));		
		float tBox23Y = (float)Math.sin(mBox2Rotation)*mBox2X[3] + (mBox2Y[3]*((float)Math.cos(mBox2Rotation)));
		
		tBox20X += mBox2PosX;
		tBox20Y += mBox2PosY;
		tBox21X += mBox2PosX;
		tBox21Y += mBox2PosY;
		tBox22X += mBox2PosX;
		tBox22Y += mBox2PosY;
		tBox23X += mBox2PosX;
		tBox23Y += mBox2PosY;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		float aURx = tBox11X;
		float aURy = tBox11Y;
		float aULx = tBox10X;
		float aULy = tBox10Y;
		float aLRx = tBox13X;
		float aLRy = tBox13Y;
		float aLLx = tBox12X;
		float aLLy = tBox12Y;
		
		
		float bULx = tBox20X;
		float bULy = tBox20Y;
		float bLLx = tBox22X;
		float bLLy = tBox22Y;
		float bURx = tBox21X;
		float bURy = tBox21Y;
		float bLRx = tBox23X;
		float bLRy = tBox23Y;
		
		float axis1X = aURx - aULx;
//		float axis1Y = aURy - aULy;
		float axis1Y = aULy - aURy;
		float axis2X = aURx - aLRx;
//		float axis2Y = aURy - aLRy;
		float axis2Y = aLRy - aURy;
		float axis3X = bULx - bLLx;
//		float axis3Y = bULy - bLLy;
		float axis3Y = bLLy - bULy;
		float axis4X = bULx - bURx;
//		float axis4Y = bULy - bURy;
		float axis4Y = bURy - bULy;
		
		
		
		
		float multiplier = 100.0f;
		g.drawLine(0, 0, (int)(axis1X * multiplier), (int)(axis1Y * multiplier));
		g.drawLine(0, 0, (int)(axis2X * multiplier), (int)(axis2Y * multiplier));
		g.drawLine(0, 0, (int)(axis3X * multiplier), (int)(axis3Y * multiplier));
	
		g.drawLine(0, 0, (int)(axis4X * multiplier), (int)(axis4Y * multiplier));
		
		float [] axisX = {axis1X, axis2X, axis3X, axis4X};
		float [] axisY = {axis1Y, axis2Y, axis3Y, axis4Y};

		
		float [] aPointsX = {aURx, aULx, aLRx, aLLx};
		float [] aPointsY = {aURy, aULy, aLRy, aLLy};

		
		float [] bPointsX = {bURx, bULx, bLRx, bLLx};
		float [] bPointsY = {bURy, bULy, bLRy, bLLy};

		
		float [] aProjectedX = new float[4];
		float [] aProjectedY = new float[4];
		
		float [] bProjectedX = new float[4];
		float [] bProjectedY = new float[4];
		
		int [] colors = {0, 0xff0000, 0x00ff00, 0x0000ff};
		int [] colors2 = {0xffff00, 0xffffff, 0x00ffff, 0xff00ff};
		
		for(int i = 0 ; i < 4; i++)
		{
			g.setColor(colors[i]);
			g.fillRect((int)aPointsX[i], (int)aPointsY[i], (int)10, (int)10);	
			g.setColor(colors2[i]);
			g.fillRect((int)bPointsX[i], (int)bPointsY[i], (int)10, (int)10);
			
		}
		
		
		for(int i = 0 ; i< 4; i++)
		{
			float lowPart = (axisX[i]*axisX[i]) + (axisY[i] * axisY[i]);
			
			float minA = 0.0f;
			float maxA = 0.0f;
			float minB = 0.0f;
			float maxB = 0.0f;
			
			for(int j = 0; j < 4; j++)
			{
				float highPart = (aPointsX[j] * axisX[i]) + (aPointsY[j] * axisY[i]);
				aProjectedX[j] = (highPart / lowPart) * axisX[i];
				aProjectedY[j] = (highPart / lowPart) * axisY[i];
				
				g.setColor(colors[j]);
				g.fillRect((int)aProjectedX[j], (int)aProjectedY[j], (int)10, (int)10);
				
				if(j == 0)
				{
					minA = (aProjectedX[j] * axisX[i]) + (aProjectedY[j] * axisY[i]);
					maxA = (aProjectedX[j] * axisX[i]) + (aProjectedY[j] * axisY[i]);
				}
				else
				{
					float candidate = (aProjectedX[j] * axisX[i]) + (aProjectedY[j] * axisY[i]);
					if(candidate < minA)
					{
						minA = candidate;
					}
					if(candidate > maxA)
					{
						maxA = candidate;
					}
				}
			}
			for(int k = 0; k < 4; k++)
			{
				float highPart = (bPointsX[k] * axisX[i]) + (bPointsY[k] * axisY[i]);
				bProjectedX[k] = (highPart / lowPart) * axisX[i];
				bProjectedY[k] = (highPart / lowPart) * axisY[i];
				
				g.setColor(colors2[k]);
				g.fillRect((int)bProjectedX[k], (int)bProjectedY[k], (int)10, (int)10);
				
				if(k == 0)
				{
					minB = (bProjectedX[k] * axisX[i]) + (bProjectedY[k] * axisY[i]);
					maxB = (bProjectedX[k] * axisX[i]) + (bProjectedY[k] * axisY[i]);
				}
				else
				{
					float candidate = (bProjectedX[k] * axisX[i]) + (bProjectedY[k] * axisY[i]);
					if(candidate < minB)
					{
						minB = candidate;
					}
					if(candidate > maxB)
					{
						maxB = candidate;
					}
				}
			}
			
//			boolean collisionOnAxis = (minB < maxA) || (maxB > minA) || (minB == maxA) || (maxB == minA);
			boolean collisionOnAxis = false;
			
			if(minB > minA)
			{

				collisionOnAxis = minB < maxA;
			}
			else
			{

				collisionOnAxis = minA < maxB;
			}
			
			
			if(!collisionOnAxis)
			{
				return false;
			}
			
		}
	
		return true;
	}
	

	
	