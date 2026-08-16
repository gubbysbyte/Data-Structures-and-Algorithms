const stoneGameIX = stones => {
    const f = [0, 0, 0];

    for (const c of stones)
        f[c % 3]++;

    if (~f[0] & 1)
        return Math.min(f[1], f[2]) > 0;

    return Math.abs(f[1] - f[2]) > 2;
};