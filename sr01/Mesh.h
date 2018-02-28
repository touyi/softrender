#pragma once
#include"Vector.h"
#include<vector>
namespace easym {
	class VertexIn
	{
	public:
		Vector4 pos;
		Vector4 color;
		Vector2 tex;
		Vector3 normal;
		VertexIn() = default;
		VertexIn(Vector4 _pos, Vector4 _color, Vector2 _tex, Vector3 _normal)
			:pos(_pos), color(_color), tex(_tex), normal(_normal) {}
		VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	};
	class Mesh
	{
	public:
		Mesh() {}

		Mesh(const Mesh& mesh) :vertices(mesh.vertices), indices(mesh.indices) {}

		Mesh(Mesh&& mesh)
		{
			swap(vertices, std::move(mesh.vertices));
			swap(indices, std::move(mesh.indices));
		}

		Mesh& operator=(const Mesh& mesh)
		{
			if (&mesh == this)
			{
				return *this;
			}
			vertices = mesh.vertices;
			indices = mesh.indices;
			return *this;
		}

		Mesh& operator=(Mesh&& mesh)
		{
			swap(vertices, std::move(mesh.vertices));
			swap(indices, std::move(mesh.indices));
			return *this;
		}

		void SetVertexs(VertexIn* _vs, int count)
		{
			vertices.resize(count);
			new(&vertices[0])std::vector<VertexIn>(_vs, _vs + count);  //vertexs.std::vector<VertexIn>::vector(_vs, _vs + count);
		}

		void SetIndices(int* _es, int count)
		{
			indices.resize(count);
			new(&indices)std::vector<UINT>(_es, _es + count); //indices.std::vector<int>::vector(_es, _es + count);
		}

		std::vector<VertexIn> vertices;
		std::vector<UINT>  indices;
	};
	
}


