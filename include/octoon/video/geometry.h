#ifndef OCTOON_GEOMETRY_H_
#define OCTOON_GEOMETRY_H_

#include <octoon/video/render_object.h>
#include <octoon/model/mesh.h>
#include <octoon/graphics/graphics_data.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT Geometry final : public RenderObject
		{
			OctoonDeclareSubClass(Geometry, RenderObject)
		public:
			Geometry() noexcept;
			~Geometry() noexcept;

			void setCastShadow(bool enable) noexcept;
			bool getCastShadow() const noexcept;

			void setReceiveShadow(bool enable) noexcept;
			bool getReceiveShadow() const noexcept;

			void setMesh(const model::MeshPtr& mesh) noexcept;
			const model::MeshPtr& getMesh() const noexcept;

			graphics::GraphicsDataPtr getVertexBuffer() const noexcept;
			graphics::GraphicsDataPtr getIndexBuffer() const noexcept;

			void setMaterial(MaterialPtr&& material) noexcept;
			void setMaterial(const MaterialPtr& material) noexcept;
			const MaterialPtr& getMaterial() const noexcept;

			void setDrawType(DrawType type) noexcept;
			DrawType getDrawType() const noexcept;

		private:
			model::MeshPtr mesh_;

			bool isCastShadow_;
			bool isReceiveShadow_;

			std::intptr_t _vertexOffset;
			std::intptr_t _indexOffset;

			MaterialPtr material_;
			DrawType drawType_;
			GraphicsIndexType indexType_;
			graphics::GraphicsDataPtr vertices_;
			graphics::GraphicsDataPtr indices_;
		};
	}
}

#endif