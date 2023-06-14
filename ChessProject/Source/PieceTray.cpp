#include "PieceTray.h"

PieceTray::PieceTray() {
    this->numOfPiece = 0;
    this->trayPoint.x = 0;
    this->trayPoint.y = 0;
}

void PieceTray::setPosition(int x, int y) {
    this->trayPoint.x = x;
    this->trayPoint.y = y;
}

void PieceTray::initpiecePositions() {
    this->numOfPiece = 0;
    this->piecePositions.resize(16);
    for (int i = 0; i < 16; ++i) {
        this->piecePositions[i].x = this->trayPoint.x + (i%4) * 40;
        this->piecePositions[i].y = this->trayPoint.y + i/4 * 40;
    }
}

void PieceTray::addPiece(Piece *piece) {
    piece->setTrayPosition(this->piecePositions[this->numOfPiece].x, this->piecePositions[this->numOfPiece].y);
    this->resizePieceSpriteIn(piece);
    this->pieceInTray.push_back(piece);
    this->numOfPiece += 1;
}

void PieceTray::removeLastPiece() {
    Piece* lastPiece = this->pieceInTray.back();
    this->resizePieceSpriteOut(lastPiece);
    this->pieceInTray.pop_back();
    this->numOfPiece -= 1;
}

void PieceTray::resizePieceSpriteOut(Piece *piece) {
    piece->spritePiece.setScale(1, 1);
}

void PieceTray::resizePieceSpriteIn(Piece *piece) {
    piece->spritePiece.setScale(0.4, 0.4);
}

void PieceTray::drawTo(sf::RenderTarget &target) {
    for (int i = 0; i < this->pieceInTray.size(); ++i) {
        this->pieceInTray[i]->renderPiece(target);
    }
}

int PieceTray::getSize() {
    return this->pieceInTray.size();
}

void PieceTray::reset() {
    this->numOfPiece = 0;
    this->pieceInTray.clear();
}

