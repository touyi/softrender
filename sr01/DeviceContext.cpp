#include "DeviceContext.h"
#include<algorithm>

namespace easym {
	DeviceContext::DeviceContext()
	{
	}


	DeviceContext::~DeviceContext()
	{
	}
	void DeviceContext::SetViewPort(int left, int top, int width, int height)
	{
		screenMat = viewport(left, top, width, height);
	}
	void DeviceContext::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation)
	{
		for (int i = startIndexLocation; i < indexCount / 3; i++) {
			VertexIn p1 = m_vertices[startVertexLocation + m_indices[i * 3]];
			VertexIn p2 = m_vertices[startVertexLocation + m_indices[i * 3 + 1]];
			VertexIn p3 = m_vertices[startVertexLocation + m_indices[i * 3 + 2]];

			VertexOut v1 = TransofrmToProjection(p1);
			VertexOut v2 = TransofrmToProjection(p2);
			VertexOut v3 = TransofrmToProjection(p3);

			if (BackFaceCulling(v1, v2, v3) == true) {
				continue;
			}

			if (Clip(v1) && Clip(v2) && Clip(v3)) {
				continue;
			}
			ToCVV(v1);
			ToCVV(v2);
			ToCVV(v3);

			TransformToScreen(screenMat, v1);
			TransformToScreen(screenMat, v2);
			TransformToScreen(screenMat, v3);

			DrawTriangle(v1, v2, v3);

		}
	}
	void DeviceContext::ToCVV(VertexOut & v)
	{
		real oneDivZ = static_cast<real>(1) / v.posH.w;
		v.posH.x *= oneDivZ;
		v.posH.y *= oneDivZ;
		v.posH.z *= oneDivZ;
		v.posH.w = 1;
	}
	bool DeviceContext::Clip(const VertexOut & v)
	{
		if (v.posH.x >= -v.posH.w && v.posH.x <= v.posH.w &&
			v.posH.y >= -v.posH.w && v.posH.y <= v.posH.w &&
			v.posH.z >= 0.f && v.posH.z <= v.posH.w)
		{
			return false;
		}
		return true;
	}
	VertexOut DeviceContext::TransofrmToProjection(const VertexIn & v)
	{
		assert(m_pShader);
		VertexOut out = m_pShader->VS(v);

		out.tex /= out.posH.w;
		return out;
	}
	void DeviceContext::TransformToScreen(const Matrix & m, VertexOut & v)
	{
		v.posH = v.posH * m;
	}
	bool DeviceContext::BackFaceCulling(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		Vector3 vec1 = v2.posH - v1.posH;
		Vector3 vec2 = v3.posH - v2.posH;
		Vector3 viewdir = v1.posH;
		Vector3 cro = Cross(vec1, vec2);
		if (Dot(cro, viewdir) > 0) {
			return false;
		}
		return true;
	}
	void DeviceContext::DrawTriangle(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		TriangleRasterization(v1, v2, v3);
	}
	void DeviceContext::TriangleRasterization(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		if (v1.posH.y == v2.posH.y) {
			if (v3.posH.y <= v1.posH.y) {
				DrawTriangleTop(v1, v2, v3);
			}
			else {
				DrawTriangleBottom(v1, v2, v3);
			}
		}
		else if (v1.posH.y == v3.posH.y) {
			if (v2.posH.y <= v1.posH.y) {
				DrawTriangleTop(v3, v1, v2);
			}
			else {
				DrawTriangleBottom(v3, v1, v2);
			}
		}
		else if (v2.posH.y == v3.posH.y) {
			if (v1.posH.y <= v2.posH.y) {
				DrawTriangleTop(v2, v3, v1);
			}
			else {
				DrawTriangleBottom(v2, v3, v1);
			}
		}
		else {
			// ÇÐ¸î
			std::vector<VertexOut>vertex{ v1,v2,v3 };
			std::sort(vertex.begin(), vertex.end(), [](const VertexOut& v1,const VertexOut& v2) {
				return v1.posH.y < v2.posH.y;
			});
			real t = (vertex[1].posH.y - vertex[0].posH.x) / (vertex[2].posH.y - vertex[0].posH.y);
			VertexOut middle = Lerp(vertex[0], vertex[2], t);
			DrawTriangleBottom(middle, vertex[1], vertex[0]);
			DrawTriangleTop(vertex[1], middle, vertex[2]);
		}
	}
	void DeviceContext::DrawTriangleTop(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
	}
	void DeviceContext::DrawTriangleBottom(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
	}
	void DeviceContext::ScanlineFill(const VertexOut & left, const VertexOut & right, int yIndex)
	{
	}
}

