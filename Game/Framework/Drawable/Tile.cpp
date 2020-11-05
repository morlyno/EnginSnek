#include "Tile.h"
#include "../VertexLayout.h"
#include "../Bindable/BindableHeaders.h"
#include "../ImGui/imgui.h"

Tile::Tile( Graphics& gfx,float x,float y,int index )
    :
    x( x ),
    y( y ),
    index( index )
{
    VertexData vd( std::move(
        VertexLayout{}
        .Add( VertexLayout::Position2D )
        //.Add( VertexLayout::Texture2D )
    ) );
    
    std::vector<unsigned short> indices;

    auto func = [&vd,&indices]()
    {
        constexpr float side = 1.0f / 2.0f;
        vd.Resize( 4u );
        vd[0].Get<VertexLayout::Position2D>() = {  side, side };
        vd[1].Get<VertexLayout::Position2D>() = {  side,-side };
        vd[2].Get<VertexLayout::Position2D>() = { -side,-side };
        vd[3].Get<VertexLayout::Position2D>() = { -side, side };

        //vd[0].Get<VertexLayout::Texture2D>() = { 0,1 };
        //vd[1].Get<VertexLayout::Texture2D>() = { 1,1 };
        //vd[2].Get<VertexLayout::Texture2D>() = { 1,0 };
        //vd[3].Get<VertexLayout::Texture2D>() = { 0,0 };

        indices.resize( 6u );
        indices[0] = 0u;
        indices[1] = 1u;
        indices[2] = 2u;

        indices[3] = 2u;
        indices[4] = 3u;
        indices[5] = 0u;
    };
    AddBind( Bind::VertexBuffer::Resolve( gfx,vd,func,"Tile" ) );
    AddBind( Bind::IndexBuffer::Resolve( gfx,indices,"Tile" ) );
    auto pvd = Bind::VertexShader::Resolve( gfx,"Tile2DVS.cso" );
    auto pvsbc = pvd->GetBytecode();
    AddBind( std::move( pvd ) );
    AddBind( Bind::PixelShader::Resolve( gfx,"Tile2DPS.cso" ) );
    struct ConstBuff
    {
        DirectX::XMFLOAT4 c = { 0.0f,1.0f,0.0f,1.0f };
    } color;
    AddBind( Bind::PixelConstantBuffer<ConstBuff>::Resolve( gfx,color,1u ) );
    AddBind( Bind::InputLayout::Resolve( gfx,vd.GetLayout(),pvsbc ) );
    AddBind( Bind::Topology::Resolve( D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
    AddBind( std::make_shared<Bind::TransformCBuf>( gfx,*this ) );
}

void Tile::Update( float dt ) noexcept
{
}

DirectX::XMMATRIX Tile::GetTransformXM() const noexcept
{
    namespace dx = DirectX;
    return
        dx::XMMatrixScaling( width,height,1.0f ) *
        dx::XMMatrixTranslation( x,y,0.0f );
}

DirectX::XMFLOAT4 Tile::GetColorXM() const noexcept
{
    return { -1.0f,-1.0f,-1.0f,-1.0f };
}

bool Tile::SpawnControlWindow() noexcept
{
    bool open = true;
    if ( ImGui::Begin( (GetType() + " " + std::to_string( index )).c_str(),&open ) )
    {
        constexpr float offset = 100.0f;
        constexpr float DragSpeed_Position = 0.1f;
        //constexpr float DragSpeed_Rotation = 1.0f;
        constexpr float DragSpeed_Scaling = 0.1f;
        const float item_width = (ImGui::GetWindowSize().x - offset) / 2.0f - 20.0f - 8.0f;

        // -----Position----- //
        ImGui::Text( "Position" );
        ImGui::PushItemWidth( item_width );

        ImGui::SameLine( offset );
        if ( ImGui::Button( "X",ImVec2( 20,0 ) ) ) { x = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##X",&x,DragSpeed_Position,0.0f,0.0f,"%.2f" );

        ImGui::SameLine();
        if ( ImGui::Button( "Y",ImVec2( 20,0 ) ) ) { y = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Y",&y,DragSpeed_Position,0.0f,0.0f,"%.2f" );

        ImGui::Text( "X" );
        ImGui::SameLine( offset );
        if ( ImGui::Button( "+##X",ImVec2( 20,0 ) ) )
            x += 1.0f;
        ImGui::SameLine( 0.0f,-1.0f );
        if ( ImGui::Button( "-##X",ImVec2( 20,0 ) ) )
            x -= 1.0f;

        ImGui::Text( "Y" );
        ImGui::SameLine( offset );
        if ( ImGui::Button( "+##Y",ImVec2( 20,0 ) ) )
            y += 1.0f;
        ImGui::SameLine( 0.0f,-1.0f );
        if ( ImGui::Button( "-##Y",ImVec2( 20,0 ) ) )
            y -= 1.0f;

        /*ImGui::SameLine();
        if ( ImGui::Button( "Z",ImVec2( 20,0 ) ) ) { z = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Z",&z,DragSpeed_Position,0.0f,0.0f,"%.2f" );*/

        // -----Rotation----- //
        /*ImGui::Text( "Rotation" );
        ImGui::SameLine( offset );

        roll = MorMath::ToDegreees( roll );
        pitch = MorMath::ToDegreees( pitch );
        yaw = MorMath::ToDegreees( yaw );

        if ( ImGui::Button( "R##Roll",ImVec2( 20,0 ) ) ) { roll = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Roll",&roll,DragSpeed_Rotation,0.0f,0.0f,"%.2f" );

        ImGui::SameLine();
        if ( ImGui::Button( "P##Pitch",ImVec2( 20,0 ) ) ) { pitch = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Pitch",&pitch,DragSpeed_Rotation,0.0f,0.0f,"%.2f" );

        ImGui::SameLine();
        if ( ImGui::Button( "Y##Yaw",ImVec2( 20,0 ) ) ) { yaw = 0.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Yaw",&yaw,DragSpeed_Rotation,0.0f,0.0f,"%.2f" );

        roll = MorMath::ToRadians( roll );
        pitch = MorMath::ToRadians( pitch );
        yaw = MorMath::ToRadians( yaw );*/

        // -----Scaling----- //
        ImGui::Text( "Scaling" );
        ImGui::SameLine( offset );

        if ( ImGui::Button( "W##Width",ImVec2( 20,0 ) ) ) { width = 1.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Width",&width,DragSpeed_Scaling,0.0f,0.0f,"%.2f" );

        ImGui::SameLine();
        if ( ImGui::Button( "H##Height",ImVec2( 20,0 ) ) ) { height = 1.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Height",&height,DragSpeed_Scaling,0.0f,0.0f,"%.2f" );

        /*ImGui::SameLine();
        if ( ImGui::Button( "D##Depth",ImVec2( 20,0 ) ) ) { scale_depth = 1.0f; }
        ImGui::SameLine( 0.0f,0.0f );
        ImGui::DragFloat( "##Depth",&scale_depth,DragSpeed_Scaling,0.0f,0.0f,"%.2f" );*/

        ImGui::PopItemWidth();

        // -----Color----- //
        /*ImGui::Text( "Color" );
        ImGui::SameLine( offset );
        ImGui::ColorEdit3( "##c",color );*/

        // -----Intensity----- //
        /*ImGui::Text( "Intesity" );
        ImGui::SameLine( offset );
        ImGui::DragFloat( "##Intesity",&specularIntesity,0.01f,0.0f,1.0f,"%.3f" );*/

        // -----Power----- //
        /*ImGui::Text( "Power" );
        ImGui::SameLine( offset );
        ImGui::DragFloat( "##Power",&specularPower,0.01f,0.0f,1.0f,"%.4f" );*/
    }
    ImGui::End();
    return open;
}


std::string Tile::GetType() const noexcept
{
    return "[Tile]";
}

void Tile::SetPos( float x,float y ) noexcept
{
    this->x = x;
    this->y = y;
}
