#pragma once
#include <so/link/so_link_event_presenter.h>
#include <mt/mt_vector.h>

// The event payload is shared with wnWarioBike; its fields are verified by both
// the rider sender and the bike receiver. Event names remain hypotheses.
struct ftWarioBikeLinkEvent : soLinkEventArgs {
    ftWarioBikeLinkEvent(int kind) : soLinkEventArgs(kind) {}
};
struct ftWarioBikeSpeedEvent : soLinkEventArgs {
    Vec2f speed;
    ftWarioBikeSpeedEvent(int kind) : soLinkEventArgs(kind) {}
};
struct ftWarioBikeTaskEvent : soLinkEventArgs {
    int taskId;
    ftWarioBikeTaskEvent(int kind, int task) : soLinkEventArgs(kind), taskId(task) {}
};
