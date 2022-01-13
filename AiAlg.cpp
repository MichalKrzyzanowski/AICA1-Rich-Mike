#include "AiAlg.h"

Move AiAlg::executeMove(sf::RenderWindow* t_window, std::array<Board*, 4> t_boards, Piece* t_piece, GameState& t_currentState)
{
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
        newMove.score = evaluate(t_currentState, &newMove, t_boards); // Call evaluate here

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

int AiAlg::evaluate(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards)
{
    int finalScore{};

    finalScore = compareScores(t_currentState, evaluateHorizontal(currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluateVertical(currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluateDiagonal(t_currentState, currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluate3DHorizontal(t_currentState, currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluate3DVertical(t_currentState, currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluate3DDiagonal(t_currentState, currentMove, boards), finalScore);
    finalScore = compareScores(t_currentState, evaluate3DStack(currentMove, boards), finalScore);

    if (finalScore > 0)
    {
        printf("YES!!");
    }

    return finalScore;
}

int AiAlg::evaluateHorizontal(Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    if (boards[currentMove->z]->owner(0, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(1, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(2, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(3, currentMove->y) == PieceCheck::AI) ++aiCount;

    if (boards[currentMove->z]->owner(0, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(1, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(2, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(3, currentMove->y) == PieceCheck::PLAYER) ++playerCount;

    if (boards[currentMove->z]->owner(0, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(1, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(2, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(3, currentMove->y) == PieceCheck::NONE) ++emptyCount;

    return calculateEvalScore(playerCount, aiCount, emptyCount);
}

int AiAlg::evaluateVertical(Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    if (boards[currentMove->z]->owner(currentMove->x, 0) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(currentMove->x, 1) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(currentMove->x, 2) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(currentMove->x, 3) == PieceCheck::AI) ++aiCount;

    if (boards[currentMove->z]->owner(currentMove->x, 0) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(currentMove->x, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(currentMove->x, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(currentMove->x, 3) == PieceCheck::PLAYER) ++playerCount;

    if (boards[currentMove->z]->owner(currentMove->x, 0) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(currentMove->x, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(currentMove->x, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(currentMove->x, 3) == PieceCheck::NONE) ++emptyCount;

    return calculateEvalScore(playerCount, aiCount, emptyCount);
}

int AiAlg::evaluateDiagonal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    int firstScore, secondScore;

    if (boards[currentMove->z]->owner(0, 0) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(1, 1) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(2, 2) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(3, 3) == PieceCheck::AI) ++aiCount;

    if (boards[currentMove->z]->owner(0, 0) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(1, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(2, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(3, 3) == PieceCheck::PLAYER) ++playerCount;

    if (boards[currentMove->z]->owner(0, 0) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(1, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(2, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(3, 3) == PieceCheck::NONE) ++emptyCount;

    firstScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[currentMove->z]->owner(0, 3) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(1, 2) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(2, 1) == PieceCheck::AI) ++aiCount;
    if (boards[currentMove->z]->owner(3, 0) == PieceCheck::AI) ++aiCount;

    if (boards[currentMove->z]->owner(0, 3) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(1, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(2, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[currentMove->z]->owner(3, 0) == PieceCheck::PLAYER) ++playerCount;

    if (boards[currentMove->z]->owner(0, 3) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(1, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(2, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[currentMove->z]->owner(3, 0) == PieceCheck::NONE) ++emptyCount;

    secondScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (t_currentState == PLAYER_TURN)
    {
        if (secondScore > firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }

    else
    {
        if (secondScore < firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }
}

int AiAlg::evaluate3DHorizontal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    int firstScore, secondScore;

    if (boards[0]->owner(0, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(1, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(2, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(3, currentMove->y) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(0, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(1, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(2, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(3, currentMove->y) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(0, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(1, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(2, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(3, currentMove->y) == PieceCheck::NONE) ++emptyCount;

    firstScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[0]->owner(3, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(2, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(1, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(0, currentMove->y) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(3, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(2, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(1, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(0, currentMove->y) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(3, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(2, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(1, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(0, currentMove->y) == PieceCheck::NONE) ++emptyCount;

    secondScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (t_currentState == PLAYER_TURN)
    {
        if (secondScore > firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }

    else
    {
        if (secondScore < firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }
}

int AiAlg::evaluate3DVertical(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    int firstScore, secondScore;

    if (boards[0]->owner(currentMove->x, 0) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(currentMove->x, 1) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(currentMove->x, 2) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(currentMove->x, 3) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(currentMove->x, 0) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(currentMove->x, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(currentMove->x, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(currentMove->x, 3) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(currentMove->x, 0) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(currentMove->x, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(currentMove->x, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(currentMove->x, 3) == PieceCheck::NONE) ++emptyCount;

    firstScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[0]->owner(currentMove->x, 3) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(currentMove->x, 2) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(currentMove->x, 1) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(currentMove->x, 0) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(currentMove->x, 3) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(currentMove->x, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(currentMove->x, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(currentMove->x, 0) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(currentMove->x, 3) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(currentMove->x, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(currentMove->x, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(currentMove->x, 0) == PieceCheck::NONE) ++emptyCount;

    secondScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (t_currentState == PLAYER_TURN)
    {
        if (secondScore > firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }

    else
    {
        if (secondScore < firstScore)
        {
            return secondScore;
        }
        else
        {
            return firstScore;
        }
    }
}

int AiAlg::evaluate3DDiagonal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    int firstScore, secondScore, thirdScore, fourthScore, tempScore;

    if (boards[0]->owner(0, 0) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(1, 1) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(2, 2) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(3, 3) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(0, 0) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(1, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(2, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(3, 3) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(0, 0) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(1, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(2, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(3, 3) == PieceCheck::NONE) ++emptyCount;

    firstScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[0]->owner(3, 3) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(2, 2) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(1, 1) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(0, 0) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(3, 3) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(2, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(1, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(0, 0) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(3, 3) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(2, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(1, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(0, 0) == PieceCheck::NONE) ++emptyCount;

    secondScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[0]->owner(0, 3) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(1, 2) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(2, 1) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(3, 0) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(0, 3) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(1, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(2, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(3, 0) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(0, 3) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(1, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(2, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(3, 0) == PieceCheck::NONE) ++emptyCount;

    thirdScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (boards[0]->owner(3, 0) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(2, 1) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(1, 2) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(0, 3) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(3, 0) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(2, 1) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(1, 2) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(0, 3) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(3, 0) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(2, 1) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(1, 2) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(0, 3) == PieceCheck::NONE) ++emptyCount;

    fourthScore = calculateEvalScore(playerCount, aiCount, emptyCount);

    if (t_currentState == PLAYER_TURN)
    {
        if (secondScore > firstScore)
        {
            tempScore = secondScore;
        }
        else
        {
            tempScore = firstScore;
        }

        if (thirdScore > tempScore) tempScore = thirdScore;
        if (fourthScore > tempScore) tempScore = fourthScore;
    }

    else
    {
        if (secondScore < firstScore)
        {
            tempScore = secondScore;
        }
        else
        {
            tempScore = firstScore;
        }

        if (thirdScore < tempScore) tempScore = thirdScore;
        if (fourthScore < tempScore) tempScore = fourthScore;
    }

    return tempScore;
}

int AiAlg::evaluate3DStack(Move* currentMove, std::array<Board*, 4> boards)
{
    int playerCount{};
    int aiCount{};
    int emptyCount{};

    if (boards[0]->owner(currentMove->x, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[1]->owner(currentMove->x, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[2]->owner(currentMove->x, currentMove->y) == PieceCheck::AI) ++aiCount;
    if (boards[3]->owner(currentMove->x, currentMove->y) == PieceCheck::AI) ++aiCount;

    if (boards[0]->owner(currentMove->x, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[1]->owner(currentMove->x, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[2]->owner(currentMove->x, currentMove->y) == PieceCheck::PLAYER) ++playerCount;
    if (boards[3]->owner(currentMove->x, currentMove->y) == PieceCheck::PLAYER) ++playerCount;

    if (boards[0]->owner(currentMove->x, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[1]->owner(currentMove->x, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[2]->owner(currentMove->x, currentMove->y) == PieceCheck::NONE) ++emptyCount;
    if (boards[3]->owner(currentMove->x, currentMove->y) == PieceCheck::NONE) ++emptyCount;

    return calculateEvalScore(playerCount, aiCount, emptyCount);
}

int AiAlg::calculateEvalScore(int playerCount, int aiCount, int emptyCount)
{
    if (playerCount == 4) return 10;
    if (playerCount == 3 && emptyCount == 1) return 6;
    if (playerCount == 2 && emptyCount == 2) return 4;

    if (aiCount == 2 && emptyCount == 2) return -4;
    if (aiCount == 3 && emptyCount == 1) return -6;
    if (aiCount == 4) return -10;
}

int AiAlg::compareScores(GameState t_currentState, int tempScore, int finalScore)
{
    if (t_currentState == PLAYER_TURN)
    {
        if (finalScore > tempScore)
        {
            return finalScore;
        }
        else
        {
            return tempScore;
        }
    }

    else
    {
        if (finalScore < tempScore)
        {
            return finalScore;
        }
        else
        {
            return tempScore;
        }
    }
}
