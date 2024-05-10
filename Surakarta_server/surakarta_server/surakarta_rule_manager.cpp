#include "surakarta_rule_manager.h"
#include <iostream>
#include <math.h>
void SurakartaRuleManager::OnUpdateBoard() {
    // TODO:
    // Every time the board and game_info is updated to the next round version, this function will be called.
    // You don't need to implement this function if you don't need it.
    // A more delicate way is to use Qt's signal and slot mechanism, but that's the advanced part.
}

int illegalmove = 0;
const int little_round[49] = {1, 6, 7, 8, 9, 10, 11, 4, 10, 16, 22, 28, 34, 29, 28, 27, 26, 25, 24, 31, 25, 19, 13, 7, 1, 6, 7, 8, 9, 10, 11, 4, 10, 16, 22, 28, 34, 29, 28, 27, 26, 25, 24, 31, 25, 19, 13, 7, 1};
const bool little_round_sign[49] = {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
const bool little_round_sign_reverse[49] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
const int big_round[49] = {2, 12, 13, 14, 15, 16, 17, 3, 9, 15, 21, 27, 33, 23, 22, 21, 20, 19, 18, 32, 26, 20, 14, 8, 2, 12, 13, 14, 15, 16, 17, 3, 9, 15, 21, 27, 33, 23, 22, 21, 20, 19, 18, 32, 26, 20, 14, 8, 2};
const bool big_round_sign[49] = {0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
const bool big_round_sign_reverse[49] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
int uid, vid;
int indicator_i, indicator_j, sum;
int mark;
int used[50];
int white_sum, black_sum;
bool search() {
    for (indicator_i = 0; indicator_i < 49; indicator_i++) {
        if (uid == little_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i + 1; indicator_j < 49; indicator_j++) {
                sum += little_round_sign[indicator_j];
                if (little_round[indicator_j] == vid) {if (sum > 0)return 1;break;}
                else if (little_round[indicator_j] == uid) {continue;}
                else if (used[little_round[indicator_j]]) {break;}
            }
        }
    }
    for (indicator_i = 48; indicator_i >=0; indicator_i--) {
        if (uid == little_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i-1; indicator_j >=0; indicator_j--) {
                sum += little_round_sign_reverse[indicator_j];
                if (little_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (little_round[indicator_j] == uid) {
                    continue;
                } else if (used[little_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    for (indicator_i = 0; indicator_i < 49; indicator_i++) {
        if (uid == big_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i + 1; indicator_j < 49; indicator_j++) {
                sum += big_round_sign[indicator_j];
                if (big_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (big_round[indicator_j] == uid) {
                    continue;
                } else if (used[big_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    for (indicator_i = 48;indicator_i>=0;indicator_i--) {
        if (uid == big_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i-1; indicator_j >=0; indicator_j--) {
                sum += big_round_sign_reverse[indicator_j];
                if (big_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (big_round[indicator_j] == uid) {
                    continue;
                } else if (used[big_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    return 0;
}

SurakartaIllegalMoveReason SurakartaRuleManager::JudgeMove(const SurakartaMove& move) {
    // TODO: Implement this function.
    if (move.player != game_info_->current_player_) {illegalmove=1;
        return SurakartaIllegalMoveReason::NOT_PLAYER_TURN;}
    if (move.to.x >= board_size_ || move.to.y >= board_size_ ) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::OUT_OF_BOARD;
    }
    if ( move.from.x >= board_size_ || move.from.y >= board_size_) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::OUT_OF_BOARD;
    }
    if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::NONE) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::NOT_PIECE;
    }
    uid = (move.from.y) * 6 + move.from.x;
    vid = (move.to.y) * 6 + move.to.x;

    // An example of how to get the color of a piece and the current player.
    /*
    for (unsigned int i = 0; i < board_size_; i++) {
        for (unsigned int j = 0; j < board_size_; j++) {
            PieceColor color = (*board_)[i][j]->GetColor();
            if (color == PieceColor::BLACK) {
                // i,j is the position of a black piece
                used[(i-1)*6+j-1]=1;
            } else if (color == PieceColor::WHITE) {
                // i,j is the position of a white piece
                used[(i-1)*6+j-1]=1;
            } else {
                used[(i-1)*6+j-1]=0;
                // i,j is an empty position
            }
        }
    }
    */
    for (indicator_i = 0; indicator_i < 6; indicator_i++)
        for (indicator_j = 0; indicator_j < 6; indicator_j++) {
            PieceColor color = (*board_)[indicator_i][indicator_j]->GetColor();
            if (color == PieceColor::NONE)
                used[(indicator_j) * 6 + indicator_i] = 0;
            else
                used[(indicator_j) * 6 + indicator_i] = 1;
        }
    SurakartaPlayer current_player = game_info_->current_player_;
    // judge piece
    PieceColor color = (*board_)[move.from.x][move.from.y]->GetColor();  // now piece color

    if (current_player == SurakartaPlayer::NONE) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::NOT_PIECE;
    } else if (current_player != color) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::NOT_PLAYER_PIECE;
    }
    // judge non capture move
        if (abs((int)move.from.x - (int)move.to.x) <= 1 && abs((int)move.from.y - (int)move.to.y) <= 1 && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::NONE) {
        return SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE;
    }
    if (abs(((int)move.from.x - (int)move.to.x) > 1 || abs((int)move.from.y - (int)move.to.y) > 1) && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::NONE) {
        illegalmove = 1;
        return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
    }

    // judge out of board

    if (current_player == SurakartaPlayer::BLACK) {
        if ((*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::BLACK) {
            illegalmove = 1;
            return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
        }

        if (search())
            return SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE;
        else {
            illegalmove = 1;
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
        }

        // black player's turn
    } else if (current_player == SurakartaPlayer::WHITE) {
        if ((*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::WHITE) {
            illegalmove = 1;
            return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
        }

        if (search())
            return SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE;
        else {
            illegalmove = 1;
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
        }
        // white player's turn
    }

    return SurakartaIllegalMoveReason::LEGAL;
}

std::pair<SurakartaEndReason, SurakartaPlayer> SurakartaRuleManager::JudgeEnd(const SurakartaIllegalMoveReason reason) {
    // TODO: Implement this function.
    // Note that at this point, the board and game_info have not been updated yet.
    black_sum = 0;
    white_sum = 0;
    for (unsigned int i = 0; i < board_size_; i++) {
        for (unsigned int j = 0; j < board_size_; j++) {
            PieceColor color = (*board_)[i][j]->GetColor();
            if (color == SurakartaPlayer::BLACK) {
                black_sum++;
            }
            if (color == SurakartaPlayer::WHITE) {
                white_sum++;
            }
        }
    }
    SurakartaPlayer current_player = game_info_->current_player_;
    /*if (illegalmove == 1)
        return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, SurakartaPlayer::NONE);
*/
    /*此部分有修改补充*/
    if((black_sum<=1)&&(current_player==SurakartaPlayer::WHITE)&&(reason==SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE))
    {return std::make_pair(SurakartaEndReason::CHECKMATE, SurakartaPlayer::WHITE);}

    if((white_sum<=1)&&(current_player==SurakartaPlayer::BLACK)&&(reason==SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE))
    {return std::make_pair(SurakartaEndReason::CHECKMATE, SurakartaPlayer::BLACK);}

    if (black_sum == 0 || white_sum == 0) {
        return std::make_pair(SurakartaEndReason::CHECKMATE, SurakartaPlayer::NONE);
    }
    if ( (reason != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) && (reason != SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE)) {
        if(current_player==SurakartaPlayer::BLACK)return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, SurakartaPlayer::WHITE);
        else return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, SurakartaPlayer::BLACK);
    }
    if((reason != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE))
    {
        if ((game_info_->num_round_)>game_info_->max_no_capture_round_-1+game_info_->last_captured_round_) {
            if(white_sum==black_sum)return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::NONE);
            else if(white_sum>black_sum)return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::WHITE);
            else return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::BLACK);

        }
    }
    return std::make_pair(SurakartaEndReason::NONE, SurakartaPlayer::NONE);
}

std::unique_ptr<std::vector<SurakartaPosition>> SurakartaRuleManager::GetAllLegalTarget(const SurakartaPosition postion) {
    // TODO:
    /*indicator_i=0,indicator_j=0;
    std::vector<SurakartaPosition> legaltargets;
    for(indicator_i=0;indicator_i<6;indicator_i++)
    {
        for(indicator_j;indicator_j<6;indicator_j++)
        {
            if(JudgeMove(&SurakartaMove(posistion.from.x,position.from.y, indicator_i, indicator_j, current_player))==SurakartaMoveReason::LEGAL)
            {
                legaltargets->push_back(*position);
            }
        }
    }*/
    // We don't test this function, you don't need to implement this function if you don't need it.
    return std::make_unique<std::vector<SurakartaPosition>>();
}

void SurakartaRuleManager::HelloWorld() {
    std::cout << "Hello World!" << std::endl;
}
