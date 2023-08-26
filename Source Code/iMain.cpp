#include "iGraphics.h"
#include "bitmap_loader.h"
#include "iostream"
#include "cmath"
#include "iostream"
#define M_PI 3.14159265358979323846
using namespace std;
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define screenWidth 1254
#define screenHeight 700
using namespace std;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
char currPage = 1;
int currLevel = 1;
int mouseX = 500, mouseY = 500;
bool music = false, intro = false;
int dl = -2; //levelComplete Delay

//Player Properties
char name[29] = "name";
int nlen = 0;
int isStart = 0;
int score[4] = {0,0,0,0};
char showScore[256] = "0";

//Gun Properties
double gunDirectionX = 1.0; // Initial gun direction (pointing to the right)
double gunDirectionY = 0.0;
// Define pivot point and angle variables
double pivotX = 63.0;
double pivotY = 132.0;
double angle = 0.0;

// Bullet properties
float dx, dy;
const double xGun = 119;
const double yGun = 138;
int r = 255, g = 255, b = 255;
double xBullet = xGun; // Initial bullet position at gun
double yBullet = yGun;
float bulletSpeed = 27.0; // Adjust this value to set the bullet speed
double bulletDirectionX = 0.0;
double bulletDirectionY = 0.0;
bool bulletFired = false;
int bulletDisplayTime = 0;
int bulletCount = 10;
int sparkDisplayTime = 0;

//Zombie properties
int zindex = 0;
struct Zombie {
	int health;
} z[4];
static int dead = 0;
//Zombie character rendering
char z2[5][30] = { "images/z2\\z1.bmp", "images/z2\\z2.bmp", "images/z2\\z3.bmp", "images/z2\\z4.bmp", "images/z2\\z5.bmp"}; //Zombie 3, Health 1
char z12[5][30] = { "images/z1\\z121.bmp", "images/z1\\z122.bmp", "images/z1\\z123.bmp", "images/z1\\z124.bmp", "images/z1\\z125.bmp" }; // Zombie 2, Health 2
char z11[5][30] = { "images/z1\\z111.bmp", "images/z1\\z112.bmp", "images/z1\\z113.bmp", "images/z1\\z114.bmp", "images/z1\\z115.bmp" }; //Zombie 2, Health 1
char z03[5][30] = { "images/z0\\z031.bmp", "images/z0\\z032.bmp", "images/z0\\z033.bmp", "images/z0\\z034.bmp", "images/z0\\z035.bmp" }; //Zombie 1, Health 3
char z02[5][30] = { "images/z0\\z021.bmp", "images/z0\\z022.bmp", "images/z0\\z023.bmp", "images/z0\\z024.bmp", "images/z0\\z025.bmp" }; //Zombie 1, Health 2
char z01[5][30] = { "images/z0\\z011.bmp", "images/z0\\z012.bmp", "images/z0\\z013.bmp", "images/z0\\z014.bmp", "images/z0\\z015.bmp" }; //Zombie 1, Health 1

//mainback
int bindex = 0;
char bg[39][30] = { "images/b\\back1.bmp", "images/b\\back2.bmp", "images/b\\back3.bmp", "images/b\\back4.bmp", "images/b\\back5.bmp", "images/b\\back6.bmp", "images/b\\back7.bmp", "images/b\\back8.bmp", "images/b\\back9.bmp", "images/b\\back10.bmp", "images/b\\back11.bmp", "images/b\\back12.bmp", "images/b\\back13.bmp"
, "images/b\\back14.bmp", "images/b\\back15.bmp", "images/b\\back16.bmp", "images/b\\back17.bmp", "images/b\\back18.bmp", "images/b\\back19.bmp", "images/b\\back20.bmp", "images/b\\back21.bmp", "images/b\\back22.bmp", "images/b\\back23.bmp", "images/b\\back24.bmp", "images/b\\back25.bmp", "images/b\\back26.bmp"
, "images/b\\back27.bmp", "images/b\\back28.bmp", "images/b\\back29.bmp", "images/b\\back30.bmp", "images/b\\back31.bmp", "images/b\\back32.bmp", "images/b\\back33.bmp", "images/b\\back34.bmp", "images/b\\back35.bmp", "images/b\\back36.bmp", "images/b\\back37.bmp", "images/b\\back38.bmp", "images/b\\back39.bmp"
};
char bg2[39][30] = { "images/b2\\back1.bmp", "images/b2\\back2.bmp", "images/b2\\back3.bmp", "images/b2\\back4.bmp", "images/b2\\back5.bmp", "images/b2\\back6.bmp", "images/b2\\back7.bmp", "images/b2\\back8.bmp", "images/b2\\back9.bmp", "images/b2\\back10.bmp", "images/b2\\back11.bmp", "images/b2\\back12.bmp", "images/b2\\back13.bmp"
, "images/b2\\back14.bmp", "images/b2\\back15.bmp", "images/b2\\back16.bmp", "images/b2\\back17.bmp", "images/b2\\back18.bmp", "images/b2\\back19.bmp", "images/b2\\back20.bmp", "images/b2\\back21.bmp", "images/b2\\back22.bmp", "images/b2\\back23.bmp", "images/b2\\back24.bmp", "images/b2\\back25.bmp", "images/b2\\back26.bmp"
, "images/b2\\back27.bmp", "images/b2\\back28.bmp", "images/b2\\back29.bmp", "images/b2\\back30.bmp", "images/b2\\back31.bmp", "images/b2\\back32.bmp", "images/b2\\back33.bmp", "images/b2\\back34.bmp", "images/b2\\back35.bmp", "images/b2\\back36.bmp", "images/b2\\back37.bmp", "images/b2\\back38.bmp", "images/b2\\back39.bmp"
};
char bg3[39][30] = { "images/b3\\back1.bmp", "images/b3\\back2.bmp", "images/b3\\back3.bmp", "images/b3\\back4.bmp", "images/b3\\back5.bmp", "images/b3\\back6.bmp", "images/b3\\back7.bmp", "images/b3\\back8.bmp", "images/b3\\back9.bmp", "images/b3\\back10.bmp", "images/b3\\back11.bmp", "images/b3\\back12.bmp", "images/b3\\back13.bmp"
, "images/b3\\back14.bmp", "images/b3\\back15.bmp", "images/b3\\back16.bmp", "images/b3\\back17.bmp", "images/b3\\back18.bmp", "images/b3\\back19.bmp", "images/b3\\back20.bmp", "images/b3\\back21.bmp", "images/b3\\back22.bmp", "images/b3\\back23.bmp", "images/b3\\back24.bmp", "images/b3\\back25.bmp", "images/b3\\back26.bmp"
, "images/b3\\back27.bmp", "images/b3\\back28.bmp", "images/b3\\back29.bmp", "images/b3\\back30.bmp", "images/b3\\back31.bmp", "images/b3\\back32.bmp", "images/b3\\back33.bmp", "images/b3\\back34.bmp", "images/b3\\back35.bmp", "images/b3\\back36.bmp", "images/b3\\back37.bmp", "images/b3\\back38.bmp", "images/b3\\back39.bmp"
};

void zrender(){
	zindex++;
	if (zindex >= 5)
		zindex = 0;
}
void brender(){
	bindex++;
	if (bindex >= 39)
		bindex = 0;
}
char kills[256] = "0";
void intToString(int number, char *buffer) {
	sprintf(buffer, "%d", number);
}

void drawEffect(){
	for (int i = 0; i < 90; ++i){
		iShowBMP2(xBullet, yBullet, "images\\ex1.bmp", 0);
	}
}

void zCollision(){
	int zc1, zc2, zc3;
	if (currLevel == 1){
		zc1 = (xBullet >= 45 && xBullet <= 156 && yBullet >= 416 && yBullet <= 507 && z[0].health > 0);
		zc2 = (xBullet >= 672 && xBullet <= 768 && yBullet >= 86 && yBullet <= 219 && z[1].health > 0);
		zc3 = (xBullet >= 1052 && xBullet <= 1120 && yBullet >= 372 && yBullet <= 493 && z[2].health > 0);
	}
	else if (currLevel == 2){
		zc1 = (xBullet >= 450 && xBullet <= 513 && yBullet >= 113 && yBullet <= 196 && z[0].health > 0);
		zc2 = (xBullet >= 672 && xBullet <= 768 && yBullet >= 86 && yBullet <= 219 && z[1].health > 0);
		zc3 = (xBullet >= 963 && xBullet <= 1037 && yBullet >= 321 && yBullet <= 426 && z[2].health > 0);
	}

	else if (currLevel == 3){
		zc1 = (xBullet >= 413 && xBullet <= 468 && yBullet >= 423 && yBullet <= 486 && z[0].health > 0);
		zc2 = (xBullet >= 956 && xBullet <= 1042 && yBullet >= 86 && yBullet <= 219 && z[1].health > 0);
		zc3 = (xBullet >= 787 && xBullet <= 869 && yBullet >= 415 && yBullet <= 505 && z[2].health > 0);
	}

	if (zc1) {
			PlaySound("music\\shoted.wav", NULL, SND_ASYNC);
			z[0].health--;
			score[currLevel] += 20;
			dead += (z[0].health == 0);
			drawEffect();
			cout << "Zombie " << 1 << " health: " << z[0].health << "\n";
			bulletFired = false; // Reset the bullet if collision occurs
			bulletDisplayTime = 0; // Reset bullet display time
	}
	else if (zc2) {
		PlaySound("music\\shoted.wav", NULL, SND_ASYNC);
		z[1].health--;
		score[currLevel] += 10;
		dead += (z[1].health == 0);
		drawEffect();
		cout << "Zombie " << 2 << " health: " << z[1].health << "\n";
		bulletFired = false; // Reset the bullet if collision occurs
		bulletDisplayTime = 0; // Reset bullet display time
	}
	else if (zc3) {
		PlaySound("music\\shoted.wav", NULL, SND_ASYNC);
		z[2].health--;
		score[currLevel] += 20;
		dead += (z[2].health == 0);
		drawEffect();
		cout << "Zombie " << 3 << " health: " << z[2].health << "\n";
		bulletFired = false; // Reset the bullet if collision occurs
		bulletDisplayTime = 0; // Reset bullet display time
	}
	intToString(dead, kills);
}

void lev1wall(){
	int wall_1 = (xBullet >= 500 && xBullet <= 543 && yBullet >= 0 && yBullet <= 460);
	int wall_2 = (yBullet >= 395 && xBullet >= 1 && xBullet <= 192);
	int wall_3 = (xBullet >= 867 && xBullet <= 1251);
	int wall_4 = (xBullet >= 501 && xBullet <= 745);

	if (wall_1){
		bulletDirectionX *= (-1);
	}
	if (wall_2){
		bulletDirectionY *= (-1);
	}

	if (wall_3){
		if (yBullet <= 364 && yBullet >= 326)
			bulletDirectionY *= (-1);
		else if (yBullet <= 325)
			bulletDirectionX *= (-1);
	}

	if (xBullet >= screenWidth || xBullet <= 0) {
		if (wall_4)
			bulletDirectionX *= (-1);
		else {
			bulletFired = false;
			bulletDisplayTime = 0;
		}
	}
	if (yBullet >= screenHeight-30 || yBullet <= 0){
		if (wall_4)
			bulletDirectionY *= (-1);
		else {
			bulletFired = false;
			bulletDisplayTime = 0;
		}
	}
}

void lev2wall(){
	//int wall1 = (xBullet >= 233 && xBullet <= 1010 && yBullet >= 653);
	int wall2 = (xBullet >= 382 && xBullet <= 435 && yBullet >= 0 && yBullet <= 362);
	int wall3 = (xBullet >= 821 && xBullet <= 869 && yBullet >= 0 && yBullet <= 470);
	int wall4 = (xBullet >= 850 && xBullet <= 1213 && yBullet >= 270 && yBullet <= 316);


	if (wall2){
		bulletDirectionX *= (-1);
	}

	if (wall3){
		bulletDirectionX *= (-1);
	}

	if (wall4){
		bulletDirectionY *= (-1);
	}

	if (xBullet >= screenWidth || xBullet <= 0) {
		bulletDirectionX *= (-1);
	}

	if (yBullet >= screenHeight-30 || yBullet <= 0){
		bulletDirectionY *= (-1);
	}

}


void lev3wall(){
	int wall1 = (xBullet >= 230 && xBullet <= 670 && yBullet >= 650);
	int wall2 = (xBullet >= 240 && xBullet <= 962 && yBullet >= 364 && yBullet <= 410);
	int wall3 = (xBullet >= 572 && xBullet <= 618 && yBullet >= 363 && yBullet <= 665);
	int wall4 = (xBullet >= 837 && xBullet <= 888 && yBullet >= 86 && yBullet <= 188);

	if (wall1){
		bulletDirectionY *= (-1);
	}

	if (wall2){
			bulletDirectionY *= (-1);
	}

	if (wall3){
		bulletDirectionX *= (-1);
	}

	if (wall4){
		bulletDirectionX *= (-1);
	}

	if (xBullet >= screenWidth || xBullet <= 0) {
		bulletDirectionX *= (-1);
	}

	if (yBullet >= screenHeight-30 || yBullet <= 0){
		bulletDirectionY *= (-1);
	}


}

void updateBulletPosition() {
	if (bulletFired && bulletDisplayTime > 0) {
		xBullet += bulletDirectionX * bulletSpeed;
		yBullet += bulletDirectionY * bulletSpeed;
		if (currLevel == 1){
			lev1wall();
		}
		else if (currLevel == 2){
			lev2wall();
		}
		else if (currLevel == 3){
			lev3wall();
		}
			
		//DisplayTime
		bulletDisplayTime--;
		//SparkDisplayTime
		sparkDisplayTime--;

		// Check for collision or screen boundaries here
		zCollision();

		// If collision or out of bounds, reset bullet position and bulletFired flag
	}
	else {
		bulletFired = false; // Reset the bullet if it's not fired or display time is over
	}
}


void drawBullet(){
		//iFilledCircle(xBullet, yBullet, 10, 1000);
		iShowBMP2(xBullet, yBullet, "images\\fire.bmp", 0);
}

void drawRotatedGun(double angle) {
	// Save the current matrix
	glPushMatrix();

	// Translate to the pivot point
	glTranslatef(pivotX, pivotY, 0.0);

	// Apply rotation around the pivot point
	glRotatef(angle, 0.0, 0.0, 1.0);

	// Draw the rotated object (e.g., gun image)
	//iShowBMP2(xGun, yGun, "images\\Gun.bmp", 0);

	glBegin(GL_POLYGON);
	glVertex2f(-20.0, -5.0);  // Vertex 1
	glVertex2f(10.0, -5.0);   // Vertex 2
	glVertex2f(10.0, 5.0);    // Vertex 3
	glVertex2f(-20.0, 5.0);   // Vertex 4
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(10.0, -2.0);   // Vertex 1
	glVertex2f(25.0, -2.0);   // Vertex 2
	glVertex2f(25.0, 2.0);    // Vertex 3
	glVertex2f(10.0, 2.0);    // Vertex 4
	glEnd();

	// Restore the saved matrix
	glPopMatrix();
}

void restart(){
	dead = 0;
	bulletCount = 10;
	bulletFired = false;
	bulletDisplayTime = 0;
	sparkDisplayTime = 0;
	intToString(0, kills);
	z[0].health = 3; //z[0].x = 50; z[0].y = 410;
	z[1].health = 2; //z[1].x = 677; z[1].y = 70;
	z[2].health = 1; //z[2].x = 1058; z[2].y = 365;
	score[1] = 0; score[2] = 0; score[3] = 0;
	strcpy(showScore, "0");
}

void Target(){
	iShowBMP2(mouseX, mouseY, "images\\target.bmp", 0);
}
void loading(){
	iShowBMP(0, 0, "images\\load.bmp");
	iSetColor(r, g, b);
	iText(screenWidth/2 , 155, name, GLUT_BITMAP_TIMES_ROMAN_24);
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;

}
void Intro(){

	loading();
	if (intro)
		currPage = 2;
}
void Menu(){
	iShowBMP(0, 0, "images\\menu.bmp");
}
void Ins(){
	iShowBMP(0, 0, "images\\inst.bmp");
	iSetColor(r, g, b);
	iText(screenWidth / 2 - 130, 150, "Press Left Mouse Button to Back", GLUT_BITMAP_TIMES_ROMAN_24);
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}
void About(){
	iShowBMP(0, 0, "images\\aboutus.bmp");
	iSetColor(r, g, b);
	iText(screenWidth / 2 - 160, 120, "Press Left Mouse Button to Back", GLUT_BITMAP_TIMES_ROMAN_24);
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}
void level_one(){
	iShowBMP(0, 0, bg[bindex]);
	iText(145, 663, "1", GLUT_BITMAP_TIMES_ROMAN_24);
	if (z[0].health == 3)
		iShowBMP2(50, 410, z03[zindex], 0);
	else if (z[0].health == 2)
		iShowBMP2(50, 410, z02[zindex], 0);
	else if (z[0].health == 1)
		iShowBMP2(50, 410, z01[zindex], 0);
	if (z[1].health == 2)
		iShowBMP2(677, 76, z12[zindex], 0);
	else if (z[1].health == 1)
		iShowBMP2(677, 76, z11[zindex], 0);
	if (z[2].health == 1){
		iShowBMP2(1058, 365, z2[zindex], 0);
	}
}
void level_two(){
	iShowBMP(0, 0, bg2[bindex]);
	iText(145, 663, "2", GLUT_BITMAP_TIMES_ROMAN_24);
	if (z[0].health == 3)
		iShowBMP2(445, 100, z03[zindex], 0);
	else if (z[0].health == 2)
		iShowBMP2(445, 100, z02[zindex], 0);
	else if (z[0].health == 1)
		iShowBMP2(445, 100, z01[zindex], 0);
	if (z[1].health == 2)
		iShowBMP2(677, 76, z12[zindex], 0);
	else if (z[1].health == 1)
		iShowBMP2(677, 76, z11[zindex], 0);
	if (z[2].health == 1){
		iShowBMP2(950, 318, z2[zindex], 0);
	}
}

void level_three(){
	iShowBMP(0, 0, bg3[bindex]);
	iText(145, 663, "3", GLUT_BITMAP_TIMES_ROMAN_24);

	if (z[0].health == 3)
		iShowBMP2(400, 399, z03[zindex], 0);
	else if (z[0].health == 2)
		iShowBMP2(400, 399, z02[zindex], 0);
	else if (z[0].health == 1)
		iShowBMP2(400, 399, z01[zindex], 0);
	if (z[1].health == 2)
		iShowBMP2(940, 76, z12[zindex], 0);
	else if (z[1].health == 1)
		iShowBMP2(940, 76, z11[zindex], 0);
	if (z[2].health == 1){
		iShowBMP2(779, 405, z2[zindex], 0);
	}
}

void Game(){
	if (currLevel == 1){
		level_one();
	}
	else if (currLevel == 2){
		level_two();
	}

	else if (currLevel == 3){
		level_three();
	}

	iShowBMP2(10, 85, "images\\Hero.bmp", 0);
	// Draw the rotated gun
	drawRotatedGun(angle);
	iSetColor(r, g, b);
	// Update and draw the bullet
	updateBulletPosition();
	if (bulletDisplayTime > 0) {
		drawBullet();
	}
	if (sparkDisplayTime > 0) {
		iShowBMP2(xGun - 20, yGun - 10, "images\\spark.bmp", 0);
	}
	iText(1215, 663, kills, GLUT_BITMAP_TIMES_ROMAN_24);
	
	for (int j = bulletCount, i=0; j>=1; i += 20,j--){
		iShowBMP2(249 + i, 10, "images\\bullet.bmp", 0);
	}
	iSetColor(255, 0, 0);
	if (dead == 3 && bulletCount >= 0) {
		currPage = 7;
		if(bulletCount>0 && bulletCount<4){
			score[currLevel] -= (4-bulletCount)*10;
		}
		intToString(score[currLevel], showScore);
		iDelay(1);
	}
	if(dead<3 && bulletCount==0){
		iDelay(1);
		currPage = 6;
	}
	
}
void levelComplete(){
	iShowBMP(0, 0, "images\\congo.bmp");
	//cout<<"Level completed\n";
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	iText(700, 290, name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(702,227,showScore,GLUT_BITMAP_TIMES_ROMAN_24);
}
void gameOver(){
	iShowBMP(0, 0, "images\\gr.bmp");
}
void levS(){
	iShowBMP(0, 0, "images\\lev.bmp");
}
void iDraw()
{
	iClear();
	if (currPage == 1) Intro();
	else if (currPage == 2) Menu();
	else if (currPage == 3) Ins();
	else if (currPage == 4) About();
	else if (currPage == 8) levS();
	else if (currPage == 5) {
		Game();
		if (music){
			iShowBMP2(0, 0, "images\\soundbtn.bmp", 0);
		}
		else iShowBMP2(0, 0, "images\\mutebtn.bmp", 0);
	}
	else if(currPage == 6) gameOver();
	else if(currPage == 7) levelComplete();
	Target();
}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	mouseX = mx - 28;
	mouseY = my - 28;

	// Calculate angle between pivot point and mouse
	double dxx = mx - pivotX;
	double dyy = my - pivotY;
	angle = atan2(dyy, dxx) * 180.0 / M_PI;
}


void iMouse(int button, int state, int mx, int my)
{
	//cout << mx << " " << my << "\n";
	if (currPage == 2){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 456 && mx <= 694 && my >= 422 && my <= 476){
			currPage = 8;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 460 && mx <= 728 && my >= 191 && my <= 240){
			currPage = 4;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 449 && mx <= 699 && my >= 306 && my <= 361){
			currPage = 3;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 464 && mx <= 753 && my >= 77 && my <= 132){
			exit(0);
		}
	}
	else if (currPage == 3){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN || mx >= 579 && mx <= 672 && my >= 73 && my <= 143){
			currPage = 2;
		}
	}
	else if (currPage == 5){
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			// Calculate bullet direction
			double dx = mx - xGun;
			double dy = my - yGun;
			PlaySound("music\\shot.wav", NULL, SND_ASYNC);
			double length = sqrt(dx * dx + dy * dy);

			if (length > 0) {
				bulletDirectionX = dx / length;
				bulletDirectionY = dy / length;
				bulletDisplayTime = 90; // Set the bullet display time (frames) here
				sparkDisplayTime = 10; // Set the spark display time (frames) here
				bulletFired = true;
				xBullet = xGun;
				yBullet = yGun;
			}
			bulletCount--;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 11 && mx <= 76 && my >= 16 && my <= 75){
			currPage = 2;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 95 && mx <= 172 && my >= 17 && my <= 79){
			restart();
			cout << "Level Restarted\n";
			currPage = 5;
		}
	}
	else if (currPage == 4){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) currPage = 2;
	}
	else if (currPage == 6){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 452 && mx <= 773 && my >= 207 && my <= 282){
			currPage = 5; 
			restart();
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 463 && mx <= 775 && my >= 83 && my <= 161){
			exit(0);
		}
	}
	else if (currPage == 7){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 456 && mx <= 593 && my >= 72 && my <= 135) {
			restart();
			currPage = 5;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 716 && mx <= 885 && my >= 75 && my <= 134) {
			restart();
			currPage = 8;
		}
	}
	else if (currPage == 8){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 242 && mx <= 449 && my >= 204 && my <= 472) {
			currLevel = 1;
			currPage = 5;
			restart();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 505 && mx <= 711 && my >= 204 && my <= 472) {
			currLevel = 2;
			currPage = 5;
			restart();
		}

		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 773 && mx <= 964 && my >= 204 && my <= 472) {
			currLevel = 3;
			currPage = 5;
			restart();
		}
		
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{


	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
    if (currPage == 1)
    {
        if (isStart)
        {
            if (key == '\b')
            {
                nlen--;
                if (nlen < 0)
                    nlen = 0;
                name[nlen] = '\0';
            }
            else if (key == '\r' && nlen > 0)
            {
                currPage = 2;
            }
            else if ((isalpha(key) || key == ' ' || key == '.') && nlen < 29)
            {
                name[nlen++] = key;
                name[nlen] = '\0';
            }
        }
        else if (!isStart)
        {
            isStart = 1;
            if (isalpha(key))
            {
                name[nlen++] = key;
                name[nlen] = '\0';
            }
        }
    }
	else if(currPage==5){
		if (key == 'm')
		{
			if (music) {
				music = false;
				PlaySound(0, 0, 0);
			}
			else {
				music = true;
				PlaySound("music\\bgm", NULL, SND_LOOP | SND_ASYNC);
			}
		}
	else if (key == 27) exit(0);
	}

}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_RIGHT)
	{

	}
	if (key == GLUT_KEY_LEFT)
	{

	}

	if (key == GLUT_KEY_HOME)
	{

	}

}


int main()
{	
	iSetTimer(150, brender);
	iSetTimer(300, zrender);
	//Define Zombies
	z[0].health = 3;
	z[1].health = 2; 
	z[2].health = 1;

	PlaySound("music\\bgm", NULL, SND_LOOP | SND_ASYNC);
	//return 0;
	iInitialize(screenWidth, screenHeight, "DeadLock");
	iStart();
	return 0;
}