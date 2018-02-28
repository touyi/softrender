#pragma once
#include"Mesh.h"
#include"Matrix.h"
#include"Texture2D.h"
namespace easym {
	class VertexOut {
	public:

		Vector4 posTrans;  //世界变换后的坐标
		Vector4 posH;      //投影变换后的坐标   
		Vector2 tex;       //纹理坐标
		Vector3 normal;    //法线
		Vector4 color;     //颜色
		real oneDivZ;     //1/z用于深度测试

		VertexOut() = default;
		VertexOut(Vector4 _posT, Vector4 _posH, Vector2 _tex, Vector3 _normal, Vector4 _color, real _oneDivZ)
			:posTrans(_posT), posH(_posH), tex(_tex), normal(_normal), color(_color), oneDivZ(_oneDivZ) {}

		VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
			color(rhs.color), oneDivZ(rhs.oneDivZ) {}

		VertexOut& operator= (const VertexOut& rhs)
		{
			if (this == &rhs)
				return *this;
			this->normal = rhs.normal;
			this->posH = rhs.posH;
			this->posTrans = rhs.posTrans;
			this->tex = rhs.tex;
			this->color = rhs.color;
			this->oneDivZ = rhs.oneDivZ;
			return *this;
		}
	};
	class BaseShader
	{
	public:
		BaseShader() {}
		virtual ~BaseShader() {}

	public:
		virtual easym::VertexOut VS(const easym::VertexIn& vin) = 0;
		virtual easym::Vector4 PS(easym::VertexOut& vout) = 0;
		virtual void SetTexture(const easym::Texture2D& tex) = 0;
		virtual void SetWorld(const easym::Matrix& world) = 0;
		virtual void SetView(const easym::Matrix& view) = 0;
		virtual void SetProject(const easym::Matrix& project) = 0;
		virtual void SetEyePos(const easym::Vector3& eyePos) = 0;
	};

	inline VertexOut Lerp(const VertexOut& a, const VertexOut& b, real t)
	{
		return VertexOut(
			easym::Lerp(a.posTrans, b.posTrans, t),
			easym::Lerp(a.posH, b.posH, t),
			easym::Lerp(a.tex, b.tex, t),
			easym::Lerp(a.normal, b.normal, t),
			easym::Lerp(a.color, b.color, t),
			easym::Lerp(a.oneDivZ, b.oneDivZ, t)
		);
	}
}


