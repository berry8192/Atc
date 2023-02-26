import statistics
import os
import joblib
import time
import optuna


n_parallel = 20
n_files = 3000


def calc_score_each(seed: int, MIN_POWER: float, MAX_POWER: float, BREAK_BEDROCK_POWER: float, KNOWN_BREAK_BASE: float, KNOWN_BREAK_TIMES: float, KNOWN_BREAK_POWER: float, ELSE_DIV: float, ELSE_TIMES: float, BINARY_BASE: float, BINARY_POWER_DIV: float, DIST_DEL: float, GEN_EXCA_BASE: float, GEN_EXCA_DIV: float, GEN_EXCA_LOG: float, GEN_EXCA_DIV_TIMES: float, GEN_EXCA_BASE_TIMES: float, IF_PRIO_TIMES: float, IF_PRIO_ADD: float, IF_POWER_TIMES: float, IF_POWER_ADD: float, ELSE_PRIO_TIMES: float, ELSE_PRIO_ADD: float, ELSE_POWER_TIMES: float, ELSE_POWER_ADD: float, GIVEUP_BASE: float, GIVEUP_DIV: float, GIVE_UP_LOG: float, EXCA_WIDTH_BASE: float, EXCA_WIDTH_TIMES: float):
    os.system(f"cargo run --release --bin tester ../a.out {MIN_POWER} {MAX_POWER} {BREAK_BEDROCK_POWER} {KNOWN_BREAK_BASE} {KNOWN_BREAK_TIMES} {KNOWN_BREAK_POWER} {ELSE_DIV} {ELSE_TIMES} {BINARY_BASE} {BINARY_POWER_DIV} {DIST_DEL} {GEN_EXCA_BASE} {GEN_EXCA_DIV} {GEN_EXCA_LOG} {GEN_EXCA_DIV_TIMES} {GEN_EXCA_BASE_TIMES} {IF_PRIO_TIMES} {IF_PRIO_ADD} {IF_POWER_TIMES} {IF_POWER_ADD} {ELSE_PRIO_TIMES} {ELSE_PRIO_ADD} {ELSE_POWER_TIMES} {ELSE_POWER_ADD} {GIVEUP_BASE} {GIVEUP_DIV} {GIVE_UP_LOG} {EXCA_WIDTH_BASE} {EXCA_WIDTH_TIMES} < ../testcases/{seed:04}.txt 1> /dev/null 2> optout/{seed:04}_score.txt")
    cmd2 = f"cat optout/{seed:04}_score.txt"
    out2 = os.popen(cmd2)
    lines = out2.readlines()
    # print(lines[-1])
    sco = int(lines[-1].split()[-1])/1.0
    # print(sco)
    return sco


def calc_scores(MIN_POWER: float, MAX_POWER: float, BREAK_BEDROCK_POWER: float, KNOWN_BREAK_BASE: float, KNOWN_BREAK_TIMES: float, KNOWN_BREAK_POWER: float, ELSE_DIV: float, ELSE_TIMES: float, BINARY_BASE: float, BINARY_POWER_DIV: float, DIST_DEL: float, GEN_EXCA_BASE: float, GEN_EXCA_DIV: float, GEN_EXCA_LOG: float, GEN_EXCA_DIV_TIMES: float, GEN_EXCA_BASE_TIMES: float, IF_PRIO_TIMES: float, IF_PRIO_ADD: float, IF_POWER_TIMES: float, IF_POWER_ADD: float, ELSE_PRIO_TIMES: float, ELSE_PRIO_ADD: float, ELSE_POWER_TIMES: float, ELSE_POWER_ADD: float, GIVEUP_BASE: float, GIVEUP_DIV: float, GIVE_UP_LOG: float, EXCA_WIDTH_BASE: float, EXCA_WIDTH_TIMES: float):
    scores = joblib.Parallel(n_jobs=n_parallel)(
        joblib.delayed(calc_score_each)(i, MIN_POWER, MAX_POWER, BREAK_BEDROCK_POWER, KNOWN_BREAK_BASE, KNOWN_BREAK_TIMES, KNOWN_BREAK_POWER, ELSE_DIV, ELSE_TIMES, BINARY_BASE, BINARY_POWER_DIV, DIST_DEL, GEN_EXCA_BASE, GEN_EXCA_DIV, GEN_EXCA_LOG, GEN_EXCA_DIV_TIMES, GEN_EXCA_BASE_TIMES, IF_PRIO_TIMES, IF_PRIO_ADD, IF_POWER_TIMES, IF_POWER_ADD, ELSE_PRIO_TIMES, ELSE_PRIO_ADD, ELSE_POWER_TIMES, ELSE_POWER_ADD, GIVEUP_BASE, GIVEUP_DIV, GIVE_UP_LOG, EXCA_WIDTH_BASE, EXCA_WIDTH_TIMES) for i in range(n_files)
    )
    # print(scores)
    return scores


def objective(trial: optuna.trial.Trial):
    start = time.time()
    MIN_POWER = trial.suggest_float("MIN_POWER", 2.0, 6.0)
    MAX_POWER = trial.suggest_float("MAX_POWER", 10.0, 60.0)
    BREAK_BEDROCK_POWER = trial.suggest_float("BREAK_BEDROCK_POWER", 1.0, 3.0)
    KNOWN_BREAK_BASE = trial.suggest_float("KNOWN_BREAK_BASE", 7.0, 15.0)
    KNOWN_BREAK_TIMES = trial.suggest_float("KNOWN_BREAK_TIMES", 0.5, 5)
    KNOWN_BREAK_POWER = trial.suggest_float("KNOWN_BREAK_POWER", 0.5, 5)
    ELSE_DIV  = trial.suggest_float("ELSE_DIV", 1.0, 30.0)
    ELSE_TIMES = trial.suggest_float("ELSE_TIMES", 0.0, 10.0)
    BINARY_BASE = trial.suggest_float("BINARY_BASE", 5.0, 30.0)
    BINARY_POWER_DIV = trial.suggest_float("BINARY_POWER_DIV", 0.9, 10.0)
    DIST_DEL = trial.suggest_float("DIST_DEL", 0.0, 20.0)
    GEN_EXCA_BASE = trial.suggest_float("GEN_EXCA_BASE", 5.0, 40.0)
    GEN_EXCA_DIV = trial.suggest_float("GEN_EXCA_DIV", 0.5, 10.0)
    GEN_EXCA_LOG = trial.suggest_float("GEN_EXCA_LOG", 0.0, 100.0)
    GEN_EXCA_DIV_TIMES = trial.suggest_float("GEN_EXCA_DIV_TIMES", 0.25, 4.0)
    GEN_EXCA_BASE_TIMES = trial.suggest_float("GEN_EXCA_BASE_TIMES", 0.25, 4.0)
    IF_PRIO_TIMES = trial.suggest_float("IF_PRIO_TIMES", 0.75, 3.0)
    IF_PRIO_ADD = trial.suggest_float("IF_PRIO_ADD", -10.0, 10.0)
    IF_POWER_TIMES = trial.suggest_float("IF_POWER_TIMES", 0.75, 3.0)
    IF_POWER_ADD = trial.suggest_float("IF_POWER_ADD", -10.0, 10.0)
    ELSE_PRIO_TIMES = trial.suggest_float("ELSE_PRIO_TIMES", 0.75, 3.0)
    ELSE_PRIO_ADD = trial.suggest_float("ELSE_PRIO_ADD", -10.0, 10.0)
    ELSE_POWER_TIMES = trial.suggest_float("ELSE_POWER_TIMES", 0.75, 3.0)
    ELSE_POWER_ADD = trial.suggest_float("ELSE_POWER_ADD", -10.0, 10.0)
    GIVEUP_BASE = trial.suggest_float("GIVEUP_BASE", 0.0, 600.0)
    GIVEUP_DIV = trial.suggest_float("GIVEUP_DIV", 100.0, 800.0)
    GIVE_UP_LOG = trial.suggest_float("GIVE_UP_LOG", -10.0, 100.0)
    EXCA_WIDTH_BASE = trial.suggest_float("EXCA_WIDTH_BASE", 0.0, 12.0)
    EXCA_WIDTH_TIMES = trial.suggest_float("EXCA_WIDTH_TIMES", -2.0, 2.0)
    scores = calc_scores(MIN_POWER, MAX_POWER, BREAK_BEDROCK_POWER, KNOWN_BREAK_BASE, KNOWN_BREAK_TIMES, KNOWN_BREAK_POWER, ELSE_DIV, ELSE_TIMES, BINARY_BASE, BINARY_POWER_DIV, DIST_DEL, GEN_EXCA_BASE, GEN_EXCA_DIV, GEN_EXCA_LOG, GEN_EXCA_DIV_TIMES, GEN_EXCA_BASE_TIMES, IF_PRIO_TIMES, IF_PRIO_ADD, IF_POWER_TIMES, IF_POWER_ADD, ELSE_PRIO_TIMES, ELSE_PRIO_ADD, ELSE_POWER_TIMES, ELSE_POWER_ADD, GIVEUP_BASE, GIVEUP_DIV, GIVE_UP_LOG, EXCA_WIDTH_BASE, EXCA_WIDTH_TIMES)
    print(f"elapsed: {time.time() - start}")
    return statistics.mean(scores)


if __name__ == "__main__":
    study = optuna.create_study(
        direction="minimize",
        study_name="tune_range",
        load_if_exists=True,
    )
    study.optimize(objective, n_trials=10000)