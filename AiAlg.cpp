#include "AiAlg.h"

Move AiAlg::executeMove(sf::RenderWindow* t_window, std::array<Board*, 4> t_boards, Piece* t_piece, GameState& t_currentState, int t_difficulty)
{
    MAX_DEPTH = t_difficulty;
    Move bestMove = getBestMove(t_currentState, t_boards, t_piece, 0, Move());
    t_boards.at(bestMove.z)->getTile(bestMove.x, bestMove.y)->owner() = t_piece->type();
    t_piece->addPosition(PieceData{ (unsigned int)bestMove.x, (unsigned int)bestMove.y, bestMove.z });
    moves.clear();
    return bestMove;
}

Move AiAlg::getBestMove(GameState t_currentState, std::array<Board*, 4> t_boards, Piece* t_piece, int t_depth, Move t_move)
{
    if (t_currentState == AI_WIN)
    {
        return Move(1000 - t_depth);
    }
    else if (t_currentState == PLAYER_WIN)
    {
        return Move(t_depth - 1000);
    }

    if (t_depth >= MAX_DEPTH)
    {
        Move newMove;
        newMove.x = t_move.x;
        newMove.y = t_move.y;
        newMove.z = t_move.z;
        newMove.score = 12; // Call evaluate here

        return newMove;
    }

    for (int z = 0; z < 4; z++)
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (t_boards.at(z)->owner(x, y) == PieceCheck::NONE)
                {
                    Move move;
                    move.x = x;
                    move.y = y;
                    move.z = z;

                    if (t_currentState == PLAYER_TURN)
                    {
                        t_boards.at(z)->getTile(x, y)->owner() = PieceCheck::PLAYER;
                        move.score = getBestMove(GameState::AI_TURN, t_boards, t_piece, t_depth + 1, move).score;
                    }
                    if (t_currentState == AI_TURN)
                    {
                        t_boards.at(z)->getTile(x, y)->owner() = PieceCheck::AI;
                        move.score = getBestMove(GameState::PLAYER_TURN, t_boards, t_piece, t_depth + 1, move).score;
                    }

                    moves.push_back(move);
                    t_boards.at(z)->getTile(x, y)->owner() = PieceCheck::NONE;
                }
            }
        }
    }

    int bestMove = 0;
    if (t_currentState == PLAYER_TURN)
    {
        int bestScore = -100000;
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (moves[i].score > bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    else
    {
        int bestScore = 100000;
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (moves[i].score < bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }

    return moves[bestMove];
}
