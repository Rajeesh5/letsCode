#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


class Observer {
public:
	virtual void update() = 0;
};


class Observable {
public:
	virtual void RegisterObserver(Observer* observer) = 0;
	virtual void unregisterObserver(Observer* observer) = 0;
	virtual void notifyObservers() = 0;
};


// Let us begin with the model, which is the most essential part of the pattern.
// The model should be able to exist independently, without views or controllers.

class StoreOrder : public Observable {
	vector<pair<string, double>> m_itemList;
	vector<Observer*> m_overservers;
public:
	StoreOrder() {}

	string getItem(int itemNum) {
		return m_itemList.at(itemNum).first;
	}
	double getPrice(int itemNum) {
		return m_itemList.at(itemNum).second;
	}
	
	vector<string, double>::iterator getItemIterator(){
		m_itemList.begin();
	}

	void deleteItem(int itemNum) {

		m_itemList.erase(std::remove(m_itemList.begin(), m_itemList.end(), m_itemList.at(itemNum)),
			m_itemList.end());

		notifyObservers();
	}
	void addItem(/*int barcode*/ pair<string, double>& item) {
		// code to add item (probably used with a scanner)
		// prices are looked up from a database
		// item = getItemFormDB(Scanner::scan(barcode));	

		m_itemList.push_back(item);
		notifyObservers();
	}
	void changePrice(int itemNum, double newPrice) {
		m_itemList.at(itemNum).second = newPrice;
		notifyObservers();
	}

	virtual void RegisterObserver(Observer* observer) override {
		m_overservers.push_back(observer);
	}
	virtual void unregisterObserver(Observer* observer) override {
		m_overservers.erase(std::remove(m_overservers.begin(), m_overservers.end(), observer), 
							m_overservers.end());
	}
	virtual void notifyObservers() override {
		// nofity to all Observers.
		for (auto observer : m_overservers) {
			observer->update();
		}
	}
};





class OrderController {
private:
	StoreOrder* m_pStoreOrder;
	OrderView* m_pOrderView;

public:
	OrderController(StoreOrder* storeOrder, OrderView* orderView) :
		m_pStoreOrder(storeOrder), m_pOrderView(orderView) {}

	void deleteItem(int itemNum) {
		m_pStoreOrder->deleteItem(itemNum);
	}

	void changePrice(int itemNum, double newPrice) {
		m_pStoreOrder->changePrice(itemNum, newPrice);
	}
};



class OrderView :public Observer /* ,ActionListener JPanel (UI_Components) */ {
	// Controller
private:
	OrderController *m_pController;

	// User-Interface Elements
	// JFrame frame;
	// JButton changePriceButton;
	// JButton deleteItemButton;
	// JTextField newPriceField;
	// JLabel totalLabel;
	// JTable groceryList;

public:

	void createUI() {
		// Initialize UI elements. e.g.:
		// deleteItemButton = new JButton("Delete Item");
		// add(deleteItemButton);
		// ...
		// Add listeners. e.g.:
		// deleteItemButton.addActionListener(this);
		// ...
	}
	
	OrderView(OrderController *controller):m_pController(controller) {		
		createUI();
	}

	void update(StoreOrder& salesOrder) {
		display(salesOrder.getItemIterator());
	}

	void display(const vector<string, double>::iterator& iter) {
		// code to display order
		//...
	}


	void actionPerformed(/*ActionEvent event*/) {
		/*
		if (event.getSource() == deleteItemButton) {
			m_pController->deleteItem(groceryList.getSelectedRow());
		}
		else if (event.getSource() == changePriceButton) {
			BigDecimal newPrice = new BigDecimal(newPriceField.getText());
			m_pController->changePrice(groceryList.getSelectedRow(), newPrice);
		}
		*/
	}
	

};


