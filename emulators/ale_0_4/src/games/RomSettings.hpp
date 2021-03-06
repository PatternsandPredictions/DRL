/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *
 * RomSettings.hpp
 *
 * The interface to describe games as RL environments. It provides terminal and
 *  reward information.
 * *****************************************************************************
 */
#ifndef __ROMSETTINGS_HPP__
#define __ROMSETTINGS_HPP__

#include "../common/Constants.h"
#include "../emucore/Serializer.hxx"
#include "../emucore/Deserializer.hxx"

class System;


// rom support interface
struct RomSettings {
    virtual ~RomSettings() {}

    // reset
    virtual void reset() = 0;

    // is end of game
    virtual bool isTerminal() const = 0;

    // get the most recently observed reward
    virtual reward_t getReward() const = 0;

    // the rom-name
    virtual const char *rom() const = 0;

    // create a new instance of the rom
    virtual RomSettings *clone() const = 0;

    // is an action part of the minimal set?
    virtual bool isMinimal(const Action &a) const = 0;

    // process the latest information from ALE
    virtual void step(const System &system) = 0;

    // saves the state of the rom settings
    virtual void saveState(Serializer & ser) = 0;
    
    // loads the state of the rom settings
    virtual void loadState(Deserializer & ser) = 0;

    // is an action legal (default: yes)
    virtual bool isLegal(const Action &a) const; 

    // Returns a restricted (minimal) set of actions. If not overriden, this is all actions.
    virtual ActionVect &getMinimalActionSet();

    // Returns the set of all legal actions
    ActionVect &getAllActions();

    // Returns a list of actions that are required to start the game.
    // By default this is an empty list.
    virtual ActionVect getStartingActions();

    protected:
      static ActionVect actions;
      static ActionVect all_actions;
};


#endif // __ROMSETTINGS_HPP__


