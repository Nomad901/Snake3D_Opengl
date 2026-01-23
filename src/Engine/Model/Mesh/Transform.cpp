#include "snkpch.h"
#include "Engine/Model/Mesh/Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SnakeEngine
{
	Transform::Transform()
	{
		mShouldBeRecomputed = false;
		mModelMat = glm::mat4(0.0f);
		mPos = glm::vec3(0.0f);
		mRotate = glm::vec3(0.0f);
		mScale = glm::vec3(0.0f);
	}
	void Transform::computeModelMatrix()
	{
		computeLocalMatrix();
		mShouldBeRecomputed = false;
	}
	void Transform::computeModelMatrix(const glm::mat4& pParent)
	{
		computeLocalMatrix();
		mModelMat *= pParent;
		mShouldBeRecomputed = false;
	}
	void Transform::setLocalPos(const glm::vec3& pPos)
	{
		mPos = pPos;
		mShouldBeRecomputed = true;
	}
	void Transform::setLocalRotation(const glm::vec3& pRotation)
	{
		mRotate = pRotation;
		mShouldBeRecomputed = true;
	}
	void Transform::setLocalScal(const glm::vec3& pScale)
	{
		mScale = pScale;
		mShouldBeRecomputed = true;
	}
	const glm::mat4& Transform::getModelMatrix() noexcept
	{
		if (mShouldBeRecomputed)
			computeModelMatrix();
		return mModelMat;
	}
	const glm::vec3& Transform::getLocalPos() const noexcept
	{
		return mPos;
	}
	const glm::vec3& Transform::getLocalRotation() const noexcept
	{
		return mRotate;
	}
	const glm::vec3& Transform::getLocalScale() const noexcept
	{
		return mScale;
	}
	void Transform::computeLocalMatrix()
	{
		const glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), mRotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), mRotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), mRotate.z, glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4 rotationMatrix = rotateX * rotateY * rotateZ;

		mModelMat = glm::translate(glm::mat4(1.0f), mPos) * rotationMatrix * glm::scale(glm::mat4(1.0f), mScale);
	}
}