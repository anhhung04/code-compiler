function rand(i, a = 0) {
    return Math.floor(Math.random() * (i - a + 1)) + a;
}
module.exports = function ({
    max_events = 1000,
    max_knights = 500,
    max_antidote = 20,
    max_phoenix = 20,
}) {
    const events = [
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 95, 96, 97, 98, 112, 113, 114,
    ];
    const nums_events = rand(
        [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
            Math.floor(Math.random() * 10)
        ) * max_events,
        1
    );
    const nums_knight = rand(
        [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
            Math.floor(Math.random() * 10)
        ) * max_knights,
        1
    );
    let event = nums_events + "\n";
    let knight = nums_knight + "\n";
    let game_events = [];
    let knights = [];
    for (let i = 0; i < nums_events; i++)
        game_events.push(events[rand(events.length - 1)]);
    for (let i = 0; i < nums_knight; i++)
        knights.push(
            [
                rand(
                    [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                        Math.floor(Math.random() * 10)
                    ) * 999,
                    1
                ),
                rand(10, 1),
                rand(max_phoenix),
                rand(
                    [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                        Math.floor(Math.random() * 10)
                    ) * 999
                ),
                rand(max_antidote),
            ].join(" ")
        );
    if (Math.random() > 0.25) game_events.push(99);
    else game_events.push(events[Math.floor(Math.random() * events.length)]);
    event += game_events.join(" ") + "\n";
    knight += knights.join("\n");
    return {
        event,
        knight,
    };
};
