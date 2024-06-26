#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex2D.h"
#include "VertexBuffer.h"

class TTFont;


/**
 * @brief 글리프를 이용해서 텍스트를 렌더링하는 셰이더입니다.
 *
 * @note
 * - 2D 텍스트 렌더링 시 기준이 되는 좌표계는 윈도우 좌표계입니다.
 */
class TextRenderer2D : public Shader
{
public:
	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 생성자입니다.
	 */
	explicit TextRenderer2D();


	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~TextRenderer2D();


	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextRenderer2D);


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 직교 투영 행렬을 설정합니다.
	 *
	 * @param ortho 설정할 직교 투영 행렬입니다.
	 */
	void SetOrtho(const Mat4x4& ortho) { ortho_ = ortho; }


	/**
	 * @brief 2D 텍스트를 그립니다.
	 * 
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param position 텍스트의 좌표입니다.
	 * @param color 텍스트의 RGBA 색상입니다.
	 */
	void DrawText2D(const TTFont* font, const std::wstring& text, const Vec2f& position, const Vec4f& color);


private:
	/**
	 * @brief 텍스트에 맞게 버텍스 버퍼를 업데이트합니다.
	 *
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param startPosition 텍스트 영역의 왼쪽 상단 좌표입니다.
	 * @param color 텍스트의 색상입니다.
	 *
	 * @return 텍스트에 맞는 버텍스의 수를 반환합니다.
	 */
	uint32_t UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& startPosition, const Vec4f& color);


private:
	/**
	 * @brief 최대 문자열의 길이입니다.
	 */
	static const int32_t MAX_STRING_LEN = 1000;


	/**
	 * @brief 글리프 정점 목록의 최대 크기입니다.
	 *
	 * @note
	 * - 문자 하나 그리는 데 필요한 정점의 수 : 6개
	 * - 만약, 최대 문자열의 길이가 1000이라면, 필요한 정점의 수 : 6 X 1000 = 6000개
	 * - 즉, 이 글리프 셰이더가 지원하는 최대 문자열의 길이는 1000이다.
	 */
	static const int32_t MAX_VERTEX_SIZE = MAX_STRING_LEN * 6;


	/**
	 * @brief 정점 목록입니다.
	 */
	std::array<VertexPositionUvColor2D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief 셰이더 내에서 사용할 정점 버퍼입니다.
	 */
	VertexBuffer vertexBuffer_;


	/**
	 * @brief 직교 투영 행렬입니다.
	 */
	Mat4x4 ortho_;
};