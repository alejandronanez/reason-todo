type todo = {
  id: int,
  text: string,
  completed: bool,
};

type state = { todos: list(todo) };

type action = 
  | Add(string)
  | Check(int)
  | Delete(int);

let toString = ReasonReact.stringToElement;
let todoId = ref(0);

let newTodo = text => {
  todoId := todoId^ + 1;
  { id: todoId^, completed: false, text };
};

let check = (id, todos) =>
  List.map(t => t.id === id ? { ... t, completed: ! t.completed } : t, todos);

let delete = (id, todos) =>
  List.filter(t => t.id !== id, todos);

let valueFromEvent = e: string => (
  e
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ... component,
  initialState: () => {
    todos: []
  },
  reducer: (action, { todos }) => 
    switch action {
    | Add(text) => ReasonReact.Update({ todos: [newTodo(text), ... todos] })
    | Check(id) => ReasonReact.Update({ todos: check(id, todos) })
    | Delete(id) => ReasonReact.Update({ todos: delete(id, todos) })
  },
  render: ({ state: {todos}, reduce}) => {
    <div className="App">
      <h3>(toString("Todo App"))</h3>
    </div>  
  }
};
