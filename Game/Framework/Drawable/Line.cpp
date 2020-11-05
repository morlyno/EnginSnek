#include "Line.h"
#include "../VertexLayout.h"
#include "../Bindable/BindableHeaders.h"
#include "../ImGui/imgui.h"

Line::Line( Graphics& gfx,int index,float x0,float y0,float length,float angle )
    :
    index( index ),
    x0( x0 ),
    y0( y0 ),
    length( length ),
    angle( angle )
{
    VertexData vd( std::move(
        VertexLayout{}
        .Add( VertexLayout::Position2D )
    ) );
    std::vector<unsigned short> indices;
    auto func = [&vd,&indices,&length]()
    {
        vd.Resize( 2u );
        vd[0].Get<VertexLayout::Position2D>() = { 0.0f,0.0f };
        vd[1].Get<VertexLayout::Position2D>() = { length,0.0f };
        indices.resize( 2u );
        indices[0] = 0u;
        indices[1] = 1u;
    };
    AddBind( Bind::VertexBuffer::Resolve( gfx,vd,func,"Line" ) );
    AddBind( Bind::IndexBuffer::Resolve( gfx,indices,"Line" ) );
    auto pvs = Bind::VertexShader::Resolve( gfx,"Line2DVS.cso" );
    auto pvsbc = pvs->GetBytecode();
    AddBind( std::move( pvs ) );
    AddBind( Bind::PixelShader::Resolve( gfx,"Line2DPS.cso" ) );
    struct ConstBuffer
    {
        DirectX::XMFLOAT4 c = { 0.5f,0.5f,0.5f,1.0f };
    } color;
    AddBind( Bind::PixelConstantBuffer<ConstBuffer>::Resolve( gfx,color,1u ) );
    AddBind( Bind::InputLayout::Resolve( gfx,vd.GetLayout(),pvsbc ) );
    AddBind( Bind::Topology::Resolve( D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST ) );
    AddBind( std::make_shared<Bind::TransformCBuf>( gfx,*this ) );
}

void Line::Update( float dt ) noexcept
{
}

DirectX::XMMATRIX Line::GetTransformXM() const noexcept
{
    namespace dx = DirectX;
    return
        dx::XMMatrixRotationZ( angle ) *
        dx::XMMatrixTranslation( x0,y0,0.0f ) *
        parentTransform;
}

DirectX::XMFLOAT4 Line::GetColorXM() const noexcept
{
    return { -1.0f,-1.0f,-1.0f,-1.0f };
}

std::string Line::GetType() const noexcept
{
    return "[Line]";
}

void Line::SetParentTransform( DirectX::FXMMATRIX matrix ) noexcept
{
    parentTransform = matrix;
}
