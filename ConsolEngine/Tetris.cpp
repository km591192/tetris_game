#include "Tetris.h"

Tetris::Tetris(int xSize, int ySize) : X_SIZE(xSize), Y_SIZE(ySize)
{
	NextFigure = (rand() % 5);
	Flag = true;
	Angle = 0;
	ClrScr();
	WinScr();
}

Tetris::~Tetris(void)
{
}

void Tetris::ClrScr(){
	for (int x = 1; x<X_SIZE + 1; x++)
	{
		for (int y = 1; y<Y_SIZE + 1; y++)
		{
			SetChar(x, y, '.');
		}
	}
}

void Tetris::UpdateF(float deltaTime)
{
	if (Flag){
		switch (NextFigure){
		case 0:	//O
			P1.X = X_SIZE/2; P1.Y = 1;
			P2.X = X_SIZE/2 + 1; P2.Y = 1;
			P3.X = X_SIZE / 2; P3.Y = 2;
			P4.X = X_SIZE / 2 + 1; P4.Y = 2;
			Symbol = 'O';
			break;
		case 1:	//S
			P1.X = X_SIZE / 2 + 1; P1.Y = 1;
			P2.X = X_SIZE / 2; P2.Y = 1;
			P3.X = X_SIZE / 2; P3.Y = 2;
			P4.X = X_SIZE / 2 - 1; P4.Y = 2;
			Symbol = 'S';
			break;
		case 2:	//I
			P1.X = X_SIZE / 2 + 1; P1.Y = 1;
			P2.X = X_SIZE / 2 + 1; P2.Y = 2;
			P3.X = X_SIZE / 2 + 1; P3.Y = 3;
			P4.X = X_SIZE / 2 + 1; P4.Y = 4;
			Symbol = 'I';
			break;
		case 3:	//J
			P1.X = X_SIZE / 2 + 1; P1.Y = 1;
			P2.X = X_SIZE / 2 + 1; P2.Y = 2;
			P3.X = X_SIZE / 2 + 1; P3.Y = 3;
			P4.X = X_SIZE / 2; P4.Y = 3;
			Symbol = 'J';
			break;
		case 4:	//T
			P1.X = X_SIZE / 2; P1.Y = 1;
			P2.X = X_SIZE / 2 + 1; P2.Y = 1;
			P3.X = X_SIZE / 2 + 2; P3.Y = 1;
			P4.X = X_SIZE / 2 + 1; P4.Y = 2;
			Symbol = 'T';
			break;
		}
		SetChar(P1.X, P1.Y, '*');
		SetChar(P2.X, P2.Y, '*');
		SetChar(P3.X, P3.Y, '*');
		SetChar(P4.X, P4.Y, '*');

		SetChar(P1.X + 12, P1.Y, '.');
		SetChar(P2.X + 12, P2.Y, '.');
		SetChar(P3.X + 12, P3.Y, '.');
		SetChar(P4.X + 12, P4.Y, '.');

		NextFigure = (rand() % 5);
		switch (NextFigure){
		case 0:	//O
			SetCharF1(Y_SIZE - 1, 1, '*');
			SetCharF1(Y_SIZE, 1, '*');
			SetCharF1(Y_SIZE - 1, 2, '*');
			SetCharF1(Y_SIZE, 2, '*');
			break;
		case 1:	//S
			SetCharF1(Y_SIZE, 1, '*');
			SetCharF1(Y_SIZE - 1, 1, '*');
			SetCharF1(Y_SIZE - 1, 2, '*');
			SetCharF1(Y_SIZE - 2, 2, '*');
			break;
		case 2:	//I
			SetCharF1(Y_SIZE, 1, '*');
			SetCharF1(Y_SIZE, 2, '*');
			SetCharF1(Y_SIZE, 3, '*');
			SetCharF1(Y_SIZE, 4, '*');
			break;
		case 3:	//J
			SetCharF1(Y_SIZE, 1, '*');
			SetCharF1(Y_SIZE, 2, '*');
			SetCharF1(Y_SIZE, 3, '*');
			SetCharF1(Y_SIZE - 1, 3, '*');
			break;
		case 4:	//T
			SetCharF1(Y_SIZE - 1, 1, '*');
			SetCharF1(Y_SIZE, 1, '*');
			SetCharF1(Y_SIZE + 1, 1, '*');
			SetCharF1(Y_SIZE, 2, '*');
			break;
		}
		Flag = false;
	}
	else
		switch (Symbol){
		case 'O':
			if ((GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
				Flag = true;
				if (P1.Y <= 1 || P2.Y <= 1)
					ClrScr();
			}
			else{
				Move();

			}
			break;
		case 'S':
			if (Angle == 0){
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					Flag = true;
					if (P1.Y <= 1 || P2.Y <= 1)
						ClrScr();
				}
				else{
					Move();
				}
			}
			else{
				if ((GetChar(P2.X, P2.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.')) {
					checkCS(P4);
				}
				else{
					Move();
				}
			}
			break;
		case 'I':
			if (Angle == 0){
				if ((GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P1);
				}
				else{
					Move();
				}
			}
			else{
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P2.X, P2.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P1);
				}
				else{
					Move();
				}
			}
			break;
		case 'J':
			switch (Angle){
			case 0:
				if ((GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P1);
				}
				else{
					Move();
				}
				break;
			case 90:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P2.X, P2.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.')) {
					checkCS(P4);
				}
				else{
					Move();
				}
				break;
			case 180:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P4);
				}
				else{
					Move();
				}
				break;
			case 270:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P2.X, P2.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P1);
				}
				else{
					Move();
				}
				break;
			}
			break;
		case 'T':
			switch (Angle){
			case 0:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P1);
				}
				else{
					Move();
				}
				break;
			case 90:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.')) {
					checkCS(P2);
				}
				else{
					Move();
				}
				break;
			case 180:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.') || (GetChar(P4.X, P4.Y + 1) != '.')) {
					checkCS(P2);
				}
				else{
					Move();
				}
				break;
			case 270:
				if ((GetChar(P1.X, P1.Y + 1) != '.') || (GetChar(P3.X, P3.Y + 1) != '.')) {
					checkCS(P2);
				}
				else{
					Move();
				}
				break;
			}
			break;
	}
	RemoveSolidLine();
}

void Tetris::MoveL(){
	SetChar(P1.X, P1.Y, '.');
	SetChar(P2.X, P2.Y, '.');
	SetChar(P3.X, P3.Y, '.');
	SetChar(P4.X, P4.Y, '.');
	SetChar(--P1.X, P1.Y, '*');
	SetChar(--P2.X, P2.Y, '*');
	SetChar(--P3.X, P3.Y, '*');
	SetChar(--P4.X, P4.Y, '*');
}

void Tetris::MoveR(){
	SetChar(P1.X, P1.Y, '.');
	SetChar(P2.X, P2.Y, '.');
	SetChar(P3.X, P3.Y, '.');
	SetChar(P4.X, P4.Y, '.');
	SetChar(++P1.X, P1.Y, '*');
	SetChar(++P2.X, P2.Y, '*');
	SetChar(++P3.X, P3.Y, '*');
	SetChar(++P4.X, P4.Y, '*');
}

void Tetris::KeyPressed(int btnCode){

	if (btnCode == 97){
		switch (Symbol){
		case 'O':
			if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P3.X - 1, P3.Y) == '.'))
				MoveL();
			break;
		case 'S':
			if ((GetChar(P1.X - 2, P2.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
				MoveL();
			break;
		case 'I':
			switch (Angle){
			case 90:
				if (GetChar(P1.X - 1, P1.Y) == '.')
					MoveL();
				break;
			case 0:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.') && (GetChar(P3.X - 1, P3.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
					MoveL();
				break;
			}
			break;
		case 'J':
			switch (Angle){
			case 0:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.') && (GetChar(P3.X - 1, P3.Y) == '.'))
					MoveL();
				break;
			case 90:
				if ((GetChar(P3.X - 1, P3.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
					MoveL();
				break;
			case 180:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.') && (GetChar(P3.X - 1, P3.Y) == '.'))
					MoveL();
				break;
			case 270:
				if ((GetChar(P3.X - 1, P3.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
					MoveL();
				break;
			}
		case 'T':
			switch (Angle){
			case 0:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
					MoveL();
				break;
			case 90:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.') && (GetChar(P3.X - 1, P3.Y) == '.'))
					MoveL();
				break;
			case 180:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.'))
					MoveL();
				break;
			case 270:
				if ((GetChar(P1.X - 1, P1.Y) == '.') && (GetChar(P2.X - 1, P2.Y) == '.') && (GetChar(P4.X - 1, P4.Y) == '.'))
					MoveL();
				break;
			}
			break;
		}
	}
	else if (btnCode == 100){
		switch (Symbol){
		case 'O':
			if ((GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
				MoveR();
			break;
		case 'S':
			if ((GetChar(P1.X + 1, P1.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.'))
				MoveR();
			break;
		case 'I':
			switch (Angle){
			case 90:
				if (GetChar(P4.X + 1, P4.Y) == '.')
					MoveR();
				break;
			case 0:
				if ((GetChar(P1.X + 1, P1.Y) == '.') && (GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
					MoveR();
				break;
			}
			break;
		case 'J':
			switch (Angle){
			case 0:
				if ((GetChar(P1.X + 1, P1.Y) == '.') && (GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.'))
					MoveR();
				break;
			case 90:
				if (GetChar(P1.X + 1, P1.Y) == '.')
					MoveR();
				break;
			case 180:
				if ((GetChar(P1.X + 1, P1.Y) == '.') && (GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
					MoveR();
				break;
			case 270:
				if ((GetChar(P3.X + 1, P3.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
					MoveR();
				break;
			}
		case 'T':
			switch (Angle){
			case 0:
				if ((GetChar(P3.X + 1, P3.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
					MoveR();
				break;
			case 90:
				if ((GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.') && (GetChar(P4.X + 1, P4.Y) == '.'))
					MoveR();
				break;
			case 180:
				if ((GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.'))
					MoveR();
				break;
			case 270:
				if ((GetChar(P1.X + 1, P1.Y) == '.') && (GetChar(P2.X + 1, P2.Y) == '.') && (GetChar(P3.X + 1, P3.Y) == '.'))
					MoveR();
				break;
			}
			break;
		}
	}
	else if (btnCode == 115){

		switch (Symbol){
		case 'O':
			while ((GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
				Move();
			}
			break;
		case 'S':
			if (Angle == 0){
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
			}
			else{
				while ((GetChar(P2.X, P2.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.')) {
					Move();
				}
				break;
		case 'I':
			if (Angle == 0){
				while ((GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
			}
			else{
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P2.X, P2.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
			}
			break;
		case 'J':
			switch (Angle){
			case 0:
				while ((GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
				break;
			case 90:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P2.X, P2.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.')) {
					Move();
				}
				break;
			case 180:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
				break;
			case 270:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P2.X, P2.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
				break;
			}
			break;
		case 'T':
			switch (Angle){
			case 0:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
				break;
			case 90:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.')) {
					Move();
				}
				break;
			case 180:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.') && (GetChar(P4.X, P4.Y + 1) == '.')) {
					Move();
				}
				break;
			case 270:
				while ((GetChar(P1.X, P1.Y + 1) == '.') && (GetChar(P3.X, P3.Y + 1) == '.')) {
					Move();
				}
				break;
			}
			break;
			}
		}
	}
	else if (btnCode == 119)
		Turn();
}


void Tetris::RemoveSolidLine(){
	for (int y = 1; y <= Y_SIZE; ++y){
		bool solid = true;
		for (int x = 1; x <= X_SIZE; ++x){
			if (GetChar(x, y) == '.'){
				solid = false;
				break;
			}
		}
		if (solid){
			for (int yy = y; yy > 1; --yy)
				for (int x = 1; x <= X_SIZE; x++)
					SetChar(x, yy, GetChar(x, yy - 1));
		}
	}
}

void Tetris::checkCS(COORD P)
{
	Flag = true;
	Angle = 0;
	if (P.Y <= 1)
		ClrScr();
}

void Tetris::WinScr()
{
	for (int x = 0; x<X_SIZE + 1; x++)
		SetCharF(x, 0, '#');
	for (int y = 0; y<Y_SIZE + 1; y++)
		SetCharF(0, y, '#');
	for (int x = 0; x<X_SIZE + 1; x++)
		SetCharF(x, Y_SIZE + 1, '#');
	for (int y = 0; y<Y_SIZE + 2; y++)
		SetCharF(X_SIZE + 1, y, '#');


	for (int x = X_SIZE + 3; x<X_SIZE + 8; x++){
		for (int y = 1; y<6; y++)
		{
			SetChar(x, y, '.');
		}
	}

	for (int x = X_SIZE + 2; x<X_SIZE + 8; x++)
		SetCharFF(x, 0, '#');
	for (int y = 0; y<6; y++)
		SetCharFF(X_SIZE + 2, y, '#');
	for (int x = X_SIZE + 2; x<X_SIZE + 9; x++)
		SetCharFF(x, 6, '#');
	for (int y = 0; y<6; y++)
		SetCharFF(X_SIZE + 8, y, '#');
}

void Tetris::Move(){
	SetChar(P1.X, P1.Y, '.');
	SetChar(P2.X, P2.Y, '.');
	SetChar(P3.X, P3.Y, '.');
	SetChar(P4.X, P4.Y, '.');
	SetChar(P1.X, ++P1.Y, '*');
	SetChar(P2.X, ++P2.Y, '*');
	SetChar(P3.X, ++P3.Y, '*');
	SetChar(P4.X, ++P4.Y, '*');
}

void Tetris::Turn(){
	switch (Symbol){
	case 'S':
		if (Angle == 0){
			if (GetChar(P3.X + 1, P3.Y) == '.' && GetChar(P4.X + 1, P4.Y - 2) == '.'){
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(++P3.X, P3.Y, '*');
				P4.Y -= 2;
				SetChar(++P4.X, P4.Y, '*');
				Angle = 90;
			}
		}
		else if (Angle == 90){
			if (GetChar(P3.X - 1, P3.Y) == '.' && GetChar(P4.X - 1, P4.Y + 2) == '.'){
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(--P3.X, P3.Y, '*');
				P4.Y += 2;
				SetChar(--P4.X, P4.Y, '*'); 
				Angle = 0; 
			}
		}		
		break;
	case 'I':
		if (Angle == 0){
			if (GetChar(P1.X - 1, P1.Y + 1) ==  '.' &&GetChar(P3.X + 1, P3.Y - 1) == '.' && GetChar(P4.X + 2, P4.Y - 2) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(--P1.X, ++P1.Y, '*');
				SetChar(++P3.X, --P3.Y, '*');
				P4.X += 2;
				P4.Y -= 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 90;
			}
		}
		else if (Angle == 90){
			if (GetChar(P1.X + 1, P1.Y - 1) == '.' && GetChar(P3.X - 1, P3.Y + 1) == '.' && GetChar(P4.X - 2, P4.Y + 2) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(++P1.X, --P1.Y, '*');
				SetChar(--P3.X, ++P3.Y, '*');
				P4.X -= 2;
				P4.Y += 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 0;
			}
		}
		break;
	case 'J':
		if (Angle == 0){
			if (GetChar(P1.X + 1, P1.Y + 1) == '.' && GetChar(P3.X - 1, P3.Y - 1) == '.' && GetChar(P4.X, P4.Y - 2) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(++P1.X, ++P1.Y, '*');
				SetChar(--P3.X, --P3.Y, '*');
				P4.Y -= 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 90;
			}
		}
		else if (Angle == 90){
			if (GetChar(P1.X - 1, P1.Y + 1) == '.' && GetChar(P3.X + 1, P3.Y - 1) == '.' && GetChar(P4.X + 2, P4.Y) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(--P1.X, ++P1.Y, '*');
				SetChar(++P3.X, --P3.Y, '*');
				P4.X += 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 180;
			}
		}
		else if (Angle == 180){
			if (GetChar(P1.X - 1, P1.Y - 1) == '.' && GetChar(P3.X + 1, P3.Y + 1) == '.' && GetChar(P4.X, P4.Y + 2) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(--P1.X, --P1.Y, '*');
				SetChar(++P3.X, ++P3.Y, '*');
				P4.Y += 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 270;
			}
		}
		else if (Angle == 270){
			if (GetChar(P1.X + 1, P1.Y - 1) == '.' && GetChar(P3.X - 1, P3.Y + 1) == '.' && GetChar(P4.X - 2, P4.Y) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P4.X, P4.Y, '.');
				SetChar(++P1.X, --P1.Y, '*');
				SetChar(--P3.X, ++P3.Y, '*');
				P4.X -= 2;
				SetChar(P4.X, P4.Y, '*');
				Angle = 0;
			}
		}
		break;
	case 'T':
		if (Angle == 0){
			if (GetChar(P1.X, P1.Y + 1) == '.' && GetChar(P3.X - 1, P3.Y + 2) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				SetChar(P1.X, ++P1.Y, '*');
				P3.Y += 2;
				SetChar(--P3.X, P3.Y, '*');
				Angle = 90;
			}
		}
		else if (Angle == 90){
			if (GetChar(P3.X + 1, P3.Y - 1) == '.'){
				SetChar(P3.X, P3.Y, '.');
				SetChar(++P3.X, --P3.Y, '*');
				Angle = 180;
			}
		}
		else if (Angle == 180){
			if (GetChar(P1.X + 1, P1.Y + 1) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(++P1.X, ++P1.Y, '*');
				Angle = 270;
			}
		}
		else if (Angle == 270){
			if (GetChar(P1.X - 1, P1.Y - 2) == '.' && GetChar(P3.X, P3.Y - 1) == '.'){
				SetChar(P1.X, P1.Y, '.');
				SetChar(P3.X, P3.Y, '.');
				P1.Y -= 2;
				SetChar(--P1.X, P1.Y, '*');
				SetChar(P3.X, --P3.Y, '*');
				Angle = 0;
			}
		}
		break;
	}
}

