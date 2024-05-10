// // #include "surakarta_agent_mine.h"

// const int value[6][6]={5,20,20,20,20,5, 20,30,50,50,30,20, 20,50,40,40,50,20, 20,50,40,40,50,20, 20,30,50,50,30,20, 5,20,20,20,20,5};
// int get_value(SurakartaPosition a,SurakartaPosition b){return value[b.y][b.x]-value[a.y][a.x];}

// SurakartaMove SurakartaAgentMine::CalculateMove() {
//     // TODO: Implement your own ai here.
//     /* 伪minmax算法
//                 function minimax(node, depth)  // 指定当前节点和搜索深度
//             // 如果能得到确定的结果或者深度为零，使用评估函数返回局面得分
//             if node is a terminal node or
//         depth = 0 return the heuristic value of node
//         // 如果轮到对手走棋，是极小节点，选择一个得分最小的走法
//         if the adversary is to play at node
//             let α : = +∞ foreach child of node
//                           α : = min(α, minimax(child, depth - 1))
//      // 如果轮到我们走棋，是极大节点，选择一个得分最大的走法
//          else {we are to play at node} let α : = -∞ foreach child of node
//          α : = max(α, minimax(child, depth - 1)) return α;*/
//     std::vector<SurakartaPosition> from;
//     std::vector<SurakartaPosition> to;

//     for (unsigned int i = 0; i < board_size_; i++) {
//         for (unsigned int j = 0; j < board_size_; j++) {
//             SurakartaPosition position = {i, j};
//             if ((*board_)[i][j]->GetColor() == game_info_->current_player_) {
//                 from.push_back(position);
//             } else {
//                 to.push_back(position);
//             }
//         }
//     }

//     SurakartaMove rd_move({0, 0}, {0, 0}, game_info_->current_player_);
//     bool flag=0;
//     int sum=-10000;

//     for (auto& p1 : from) {
//         for (auto& p2 : to) {
//             SurakartaMove move = {p1, p2, game_info_->current_player_};
//             SurakartaIllegalMoveReason reason = rule_manager_->JudgeMove(move);
//             if (reason == SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {
//                 if(get_value(p1,p2)>sum){rd_move=move;sum=get_value(p1,p2);flag=1;}
//             }
//         }
//     }
//     if(flag)return rd_move;
//     for (auto& p1 : from) {
//         for (auto& p2 : to) {
//             SurakartaMove move = {p1, p2, game_info_->current_player_};
//             SurakartaIllegalMoveReason reason = rule_manager_->JudgeMove(move);
//             if (reason == SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE) {
//                 if(get_value(p1,p2)>sum){rd_move=move;sum=get_value(p1,p2);flag=1;}
//             }
//         }
//     }
//     return rd_move;
// }
