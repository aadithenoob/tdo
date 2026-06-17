# tdo - Task Manager CLI

An interactive task manager CLI, written in C.

## Functionality

`tdo` uses an interactive loop to read commands and perform actions on `tasks.md`, where tasks are stored.

## Commands

1. ### `add <task text>`

    Appends the provided task along with its task number to `tasks.md`, then prints a confirmation. (Creates `tasks.md` if it doesn't exist.)

    ### Usage

    ```
    $ ./tdo
    --- Task Manager ---

    > add buy milk
    Task added.

    > add go for a walk
    Task added.
    ```

2. ### `view`

    Displays the contents of `tasks.md`.

    ### Usage

    ```
    > view
    1 buy milk
    2 go for a walk
    ```

3. ### `delete <task number>` (upcoming)

    Removes the task associated with the provided task number from `tasks.md`.

    ### Usage

    *(will be added)*

## Building

Compile the program:

```bash
gcc tdo.c -o tdo
```

Run it:

```bash
./tdo
```

## Future Plans

* Persist task numbering between sessions.
* Implement the `delete` command.
