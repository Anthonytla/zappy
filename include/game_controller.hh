#pragma once
#include <vector>

#include "game_view.hh"
#include "game_model.hh"
class GameController{
    public:
    GameController(View &view, Model &model):view_(view), model_(model){};
    View& getView();

    Model &getModel();

    std::string apply_action(int id, std::string command);

    void update_view();
    private:
    View &view_;
    Model &model_;
    
};