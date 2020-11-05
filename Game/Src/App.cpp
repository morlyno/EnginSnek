#include "App.h"
#include "../Framework/ImGui/imgui.h"
#include "../Framework/Utility/MorUtility.h"
#include "../Framework/Drawable/DrawableHeader.h"

#define gfx wnd.Gfx()

App::App()
	:
	wnd( 1200,800,L"SexyWindow" ),
	cam( 12.5f,12.5f,-20.0f,0.0f,0.0f ),
	brd( gfx,Vec2{ 0.0f,0.0f },Vei2{ 25,25 },std::mt19937( std::random_device{}() ) ),
	snek( { 2,2 },gfx )
{
	wnd.Gfx().SetProjection( DirectX::XMMatrixPerspectiveLH( 1.0f,(float)wnd.GetHeight() / (float)wnd.GetWidth(),0.5f,400.0f ) );
}

App::~App()
{
}

int App::Go()
{
	while ( true )
	{
		if ( wnd.kbd.KeyIsPresst( 'Q' ) )
			wnd.Kill();
		if ( const auto ecode = Window::ProcessingMessage() )
		{
			return *ecode;
		}
		wnd.Gfx().ClearBuffer( c[0],c[1],c[2] );
		imgui.StartFrame();
		DoFrame();
		ImGuiWindows();
		imgui.Render();
		wnd.Gfx().EndFrame();
	}
}

void App::DoFrame()
{
	wnd.Gfx().SetCamera( cam );
	timer.Mark();

	if ( !GameOver )
	{

		if ( wnd.kbd.KeyIsPresst( 'W' ) )
		{
			dir = { 0,1 };
		}
		else if ( wnd.kbd.KeyIsPresst( 'S' ) )
		{
			dir = { 0,-1 };
		}
		else if ( wnd.kbd.KeyIsPresst( 'A' ) )
		{
			dir = { -1,0 };
		}
		else if ( wnd.kbd.KeyIsPresst( 'D' ) )
		{
			dir = { 1,0 };
		}
		snek.SetDir( dir );
		deltaTime += paused ? 0.0f : timer.LastDuration() * SimulationSpeed;
		while ( deltaTime > SleepTime )
		{
			deltaTime -= SleepTime;
			if ( !snek.Move( brd ) )
			{
				GameOver = true;
			}
		}
		snek.CheckForFrute( brd );
	}
	else
	{
		ImGui::Begin( "GameOver" );
		ImGui::End();
		if ( wnd.kbd.KeyIsPresst( VK_SPACE ) )
		{
			GameOver = false;
			snek.Reset();
		}
	}
	brd.Draw();
	snek.Draw();
}

void App::ImGuiWindows() noexcept
{
	SpawnDrawableControlWindowMangerWindow();
	SpawnDrawableControlWindows();
	SpawnSimulationWindow();
	cam.ShowControlWindow();
}

void App::SpawnSimulationWindow() noexcept
{
	if ( ImGui::Begin( "Simulation Control" ) )
	{
		ImGui::ColorEdit3( "Background",c );
		ImGui::SliderFloat( "Speed Factor",&SimulationSpeed,0.0f,10.0f );
		if ( ImGui::Button( "Reset" ) )
			SimulationSpeed = 1.0f;
		ImGui::SameLine();
		if ( ImGui::Button( "x2" ) )
			SimulationSpeed = 2.0f;
		ImGui::SameLine();
		if ( ImGui::Button( "x0.5" ) )
			SimulationSpeed = 0.5f;
		ImGui::Checkbox( "Pause",&paused );
		const float lastdurr = timer.LastDuration();
		ImGui::Text( paused ? "(Paused)" : ("ms/Frame:" + std::to_string( lastdurr * 1000.0f ) + "  FPS: " + std::to_string( 1.0f / lastdurr )).c_str() );
	}
	ImGui::End();
}

void App::SpawnDrawableControlWindowMangerWindow() noexcept
{
	//if ( ImGui::Begin( "Drawables" ) )
	//{
	//	if ( ImGui::BeginCombo( "Index",index ? std::to_string( index.value() ).c_str() : "Select Drawable..." ) )
	//	{
	//		for ( int i = 0; i < drawables.size(); ++i )
	//		{
	//			const bool selected = i == index;
	//			if ( ImGui::Selectable( (std::to_string( i ) + " " + drawables[i]->GetType()).c_str(),selected ) )
	//			{
	//				index = i;
	//			}
	//		}
	//		ImGui::EndCombo();
	//	}
	//	if ( ImGui::Button( "Spawn Window" ) && index )
	//	{
	//		DrawableId.insert( *index );
	//		index.reset();
	//	}
	//	if ( ImGui::Button( "Erase Drawable" ) && index )
	//	{
	//		Mor::Utility::erase_by_index( drawables,*index );
	//		index.reset();
	//	}
	//}
	//ImGui::End();
}

void App::SpawnDrawableControlWindows() noexcept
{
	//for ( auto i = DrawableId.begin(); i != DrawableId.end(); )
	//{
	//	if ( !drawables[*i]->SpawnControlWindow() )
	//	{
	//		i = DrawableId.erase( i );
	//		continue;
	//	}
	//	++i;
	//}
}

#undef gfx