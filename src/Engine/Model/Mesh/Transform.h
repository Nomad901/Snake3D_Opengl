#pragma once

namespace SnakeEngine
{
	class Transform
	{
	public:
		Transform();

		void computeModelMatrix();
		void computeModelMatrix(const glm::mat4& pParent);

		void setLocalPos(const glm::vec3& pPos);
		void setLocalRotation(const glm::vec3& pRotation);
		void setLocalScal(const glm::vec3& pScale);

		const glm::mat4& getModelMatrix() noexcept;
		const glm::vec3& getLocalPos() const noexcept;
		const glm::vec3& getLocalRotation() const noexcept;
		const glm::vec3& getLocalScale() const noexcept;

	private:
		void computeLocalMatrix();

	private:
		glm::mat4 mModelMat;

		glm::vec3 mPos;
		glm::vec3 mRotate;
		glm::vec3 mScale;

		bool mShouldBeRecomputed;
	};
}