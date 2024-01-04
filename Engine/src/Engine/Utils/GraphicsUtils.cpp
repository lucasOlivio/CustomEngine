#include "pch.h"

#include "GraphicsUtils.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
	void GraphicsUtils::DrawModel(glm::mat4 matModel,
								  bool isWireFrame,
								  bool doNotLight,
								  bool useColorTexture,
								  int VAO_ID,
								  int numberOfIndices)
	{
		iShaderProgram* pShader = ShaderManager::GetActiveShader();

		// Update model matrix on shader
		pShader->SetUniformMatrix4f("matModel", matModel);

		// Also calculate and pass the "inverse transpose" for the model matrix
		glm::mat4 matModelIT = glm::inverse(glm::transpose(matModel));
		pShader->SetUniformMatrix4f("matModel_IT", matModelIT);

		pShader->IsWireframe(isWireFrame);
		pShader->SetUniformFloat("doNotLight", doNotLight);
		pShader->SetUniformFloat("bUseColorTexture", useColorTexture);

		glBindVertexArray(VAO_ID); //  enable VAO (and everything else)
		glDrawElements(GL_TRIANGLES,
			numberOfIndices,
			GL_UNSIGNED_INT,
			0);
		glBindVertexArray(0); 			  // disable VAO (and everything else)
	}

	void GraphicsUtils::DrawTiledModel(glm::vec3 axis,
									   glm::vec3 offset,
									   glm::mat4 matModel,
									   bool isWireFrame,
									   bool doNotLight,
									   bool useColorTexture,
									   int VAO_ID,
									   int numberOfIndices)
	{
		//// Default we only draw 1 time in each axis
		//vec3 axis = vec3(1.0);
		//vec3 offset = vec3(0.0);
		//// If has tiling then we draw X times per axis based on the offset
		//if (pTilingComp)
		//{
		//	TilingComponent* pTiling = (TilingComponent*)pTilingComp;
		//	axis = pTiling->GetAxis();
		//	offset = pTiling->GetOffset();
		//}

		//pTransform->SetFramePosition();

		//// Now go for each axis tiling to draw adding the offset
		//for (int x = 0; x < axis[0]; x++)
		//{
		//	for (int y = 0; y < axis[1]; y++)
		//	{
		//		for (int z = 0; z < axis[2]; z++)
		//		{
		//			vec3 delta = offset;
		//			delta.x = offset.x * x;
		//			delta.y = offset.y * y;
		//			delta.z = offset.z * z;
		//			pTransform->Move(delta);

		//			// If the model have a parent we must use the parents transform
		//			mat4 transformMat = mat4(1.0);
		//			if (pModel->parentTagName != "")
		//			{
		//				TransformComponent* parentTransform = m_pSceneView->GetComponentByTag<TransformComponent>(pModel->parentTagName, "transform");

		//				transformMat = parentTransform->GetTransformNoScale();
		//			}

		//			UpdateTransform(pTransform->GetTransform(transformMat));

		//			// Model update and render
		//			pModel->Update(deltaTime);

		//			sMesh* currMesh = pModel->GetCurrentMesh();
		//			Draw(pModel->isWireframe,
		//				pModel->doNotLight,
		//				pModel->useColorTexture,
		//				currMesh->VAO_ID,
		//				currMesh->numberOfIndices);

		//			// Come back to initial frame place
		//			pTransform->ResetFramePosition();
		//		}
		//	}
		//}
	}
}
