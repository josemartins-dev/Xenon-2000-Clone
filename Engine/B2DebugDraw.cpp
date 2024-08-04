#include "B2DebugDraw.h"
#include <vector>
#include <SDL.h>

void B2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<SDL_Point> sdlVertices(vertexCount);
	for (int i = 0; i < vertexCount; ++i) {
		sdlVertices[i].x = static_cast<int>(vertices[i].x * pixelsPerMeter);
		sdlVertices[i].y = static_cast<int>(vertices[i].y * pixelsPerMeter);
	}

	SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
	SDL_RenderDrawLines(m_renderer, sdlVertices.data(), vertexCount);
	SDL_RenderDrawLine(m_renderer, sdlVertices[vertexCount - 1].x, sdlVertices[vertexCount - 1].y, sdlVertices[0].x, sdlVertices[0].y);
}

void B2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<SDL_Point> sdlVertices(vertexCount);
	for (int i = 0; i < vertexCount; ++i) {
		sdlVertices[i].x = static_cast<int>(vertices[i].x * pixelsPerMeter);
		sdlVertices[i].y = static_cast<int>(vertices[i].y * pixelsPerMeter);
	}

	SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
	SDL_RenderDrawLines(m_renderer, sdlVertices.data(), vertexCount);
	SDL_RenderDrawLine(m_renderer, sdlVertices[vertexCount - 1].x, sdlVertices[vertexCount - 1].y, sdlVertices[0].x, sdlVertices[0].y);
}
