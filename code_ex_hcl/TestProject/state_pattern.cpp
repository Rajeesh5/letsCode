#include <iostream>

using namespace std;


//fwd declration.
class Entity;
class OpnedState;
class ResolvedState;
class RejectedState;
class ClosedState;




//Defect state like: Submitted,Opened,Resolved,Rejected,Closed
class EntityState {
public:
	virtual void Submited(Entity*)=0;
	virtual void Opened(Entity*)=0;
	virtual void Resolved(Entity*)=0;
	virtual void Rejected(Entity*)=0;
	virtual void Closed(Entity*)=0;
protected:
	string m_stateName;
};


class SubmitedState: public EntityState {
public:
	SubmitedState() {
		m_stateName = "Submitted";
	}
	virtual void Submited(Entity* ent){}
	virtual void Opened(Entity* ent)  {
		ent->ClearState();
		ent->SetState(new OpnedState());
		//Perform state-change action.	
	}
	virtual void Resolved(Entity* ent){}
	virtual void Rejected(Entity* ent){}
	virtual void Closed(Entity* ent)  {}
};
class OpnedState : public EntityState {
public:
	OpnedState() {
		m_stateName = "Opned";
	}
	virtual void Submited(Entity* ent) {}
	virtual void Opened(Entity* ent) {}
	virtual void Resolved(Entity* ent) {}
	virtual void Rejected(Entity* ent) {}
	virtual void Closed(Entity* ent) {}
};
class ResolvedState : public EntityState {
public:
	virtual void Submited(Entity* ent) {}
	virtual void Opened(Entity* ent) {}
	virtual void Resolved(Entity* ent) {}
	virtual void Rejected(Entity* ent) {}
	virtual void Closed(Entity* ent) {}
};
class RejectedState : public EntityState {
public:
	virtual void Submited(Entity* ent) {}
	virtual void Opened(Entity* ent) {}
	virtual void Resolved(Entity* ent) {}
	virtual void Rejected(Entity* ent) {}
	virtual void Closed(Entity* ent) {}
};
class ClosedState : public EntityState {
public:
	virtual void Submited(Entity* ent) {}
	virtual void Opened(Entity* ent) {}
	virtual void Resolved(Entity* ent) {}
	virtual void Rejected(Entity* ent) {}
	virtual void Closed(Entity* ent) {}
};


// statefull entity, like defect.
class Entity {
public:
	Entity(const string name) :m_name(name) {
		m_state = new SubmitedState();
	}
	void SetState(EntityState* state) { m_state = state; }
	void ClearState() { delete m_state; }
	void Submit() { m_state->Submited(this); };
	void Open() { m_state->Opened(this); };
	void Resolve() { m_state->Resolved(this); }
	void Reject() { m_state->Rejected(this); }
	void Close() { m_state->Closed(this); }

private:
	EntityState* m_state;
	string m_name;
};


int main() {

	Entity defect("SAMPL_Defect");	// Default state is: Submitted
	defect.Open();
	defect.Resolve();
	defect.Reject();				// Invalid move..
	defect.Close();


}