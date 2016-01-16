#ifndef MICON_BEHAVIOR_H
#define MICON_BEHAVIOR_H

class MiconBehavior {
public:
    static void run_normal();
    static void run_keeper();
    static void run_line_trace();
    static void run_kamikaze();
    static void run_debug_compass();
    static void run_debug_line();
    static void run_debug_kicker();
    static void run_debug_dribbler();

private:
    MiconBehavior();
};

void MiconBehavior::run_normal() {}
void MiconBehavior::run_keeper() {}
void MiconBehavior::run_line_trace() {}
void MiconBehavior::run_kamikaze() {}
void MiconBehavior::run_debug_compass() {}
void MiconBehavior::run_debug_line() {}
void MiconBehavior::run_debug_kicker() {}
void MiconBehavior::run_debug_dribbler() {}

#endif /* MICON_BEHAVIOR_H */
