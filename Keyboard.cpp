
#include "Keyboard.h"


KeyboardClient::KeyboardClient(  KeyboardServer& kServer )
	: server( kServer )
{}

bool KeyboardClient::UpIsPressed() const
{
	return server.upIsPressed;
}
bool KeyboardClient::DownIsPressed() const
{
	return server.downIsPressed;
}
void KeyboardClient::ResetSpaceIsReleased()
{
	server.spaceIsReleased = false;
}
bool KeyboardClient::LeftIsPressed() const
{
	return server.leftIsPressed;
}
bool KeyboardClient::RightIsPressed() const
{
	return server.rightIsPressed;
}
bool KeyboardClient::SpaceIsPressed() const
{
	return server.spaceIsPressed;
}
bool KeyboardClient::EnterIsPressed() const
{
	return server.enterIsPressed;
}
bool KeyboardClient::SpaceIsRealesed() const
{
	return server.spaceIsReleased;   //∑µªÿ“ª¥Œclick

}



KeyboardServer::KeyboardServer()
:	upIsPressed( false ),
	downIsPressed( false ),
	leftIsPressed( false ),
	rightIsPressed( false ),
	spaceIsPressed( false ),
	enterIsPressed( false )
{}
bool spaceinterval = true;
void KeyboardServer::OnUpPressed()
{
	if (spaceinterval)
	upIsPressed = true;
}
void KeyboardServer::OnDownPressed()
{   
	if (spaceinterval)
	downIsPressed = true;
	
}
void KeyboardServer::OnLeftPressed()
{   
	if (spaceinterval)
	leftIsPressed = true;
}
void KeyboardServer::OnRightPressed()
{   
	if (spaceinterval)
	rightIsPressed = true;
}

UINT_PTR iTimerID;
void CALLBACK relock(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	spaceinterval =true;
	KillTimer(NULL, iTimerID);
}	


void KeyboardServer::OnSpacePressed()
{
	if (spaceinterval)
	{
	
		spaceinterval = false;
		spaceIsPressed = true;
		iTimerID= SetTimer(NULL, 10, 500, relock);

	}
	else spaceIsPressed = false;
}
void KeyboardServer::OnEnterPressed()
{ 
	enterIsPressed = true;
}

void KeyboardServer::OnUpReleased()
{

	upIsPressed = false;
}
void KeyboardServer::OnDownReleased()
{
	downIsPressed = false;
}
void KeyboardServer::OnLeftReleased()
{
	leftIsPressed = false;
}
void KeyboardServer::OnRightReleased()
{
	rightIsPressed = false;
}
void KeyboardServer::OnSpaceReleased()
{
	spaceIsPressed = false;
}
void KeyboardServer::OnEnterReleased()
{
	enterIsPressed = false;
}
