<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes">
  <title>Stock Price Management System</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: 'Segoe UI', Roboto, 'Helvetica Neue', sans-serif;
    }

    body {
      background: linear-gradient(145deg, #e9f0f5 0%, #d4e0e8 100%);
      min-height: 100vh;
      padding: 2rem 1.5rem;
    }

    /* main container */
    .app-container {
      max-width: 1400px;
      margin: 0 auto;
    }

    /* header */
    .header {
      text-align: center;
      margin-bottom: 2rem;
    }

    .header h1 {
      font-size: 2.2rem;
      background: linear-gradient(135deg, #1a2a3a, #0f212f);
      background-clip: text;
      -webkit-background-clip: text;
      color: transparent;
      letter-spacing: -0.5px;
      text-shadow: 2px 2px 8px rgba(0,0,0,0.05);
    }

    .header p {
      color: #2c3e4e;
      margin-top: 0.5rem;
      font-weight: 500;
    }

    /* card style */
    .card {
      background: rgba(255, 255, 255, 0.92);
      backdrop-filter: blur(2px);
      border-radius: 32px;
      box-shadow: 0 20px 35px -12px rgba(0, 0, 0, 0.2);
      padding: 1.6rem 2rem;
      margin-bottom: 2rem;
      transition: all 0.2s ease;
      border: 1px solid rgba(255,255,255,0.5);
    }

    .card h2 {
      display: flex;
      align-items: center;
      gap: 0.5rem;
      font-size: 1.6rem;
      font-weight: 600;
      color: #1e2f3c;
      border-left: 5px solid #2c7da0;
      padding-left: 1rem;
      margin-bottom: 1.3rem;
    }

    .grid-2col {
      display: flex;
      flex-wrap: wrap;
      gap: 2rem;
    }

    .form-panel, .search-panel {
      flex: 1;
      min-width: 260px;
    }

    .input-group {
      margin-bottom: 1.2rem;
      display: flex;
      flex-direction: column;
    }

    .input-group label {
      font-weight: 600;
      margin-bottom: 0.4rem;
      color: #1f5068;
      font-size: 0.85rem;
      letter-spacing: 0.5px;
    }

    .input-group input {
      padding: 0.8rem 1rem;
      border-radius: 24px;
      border: 1px solid #cbdbe2;
      background: white;
      font-size: 1rem;
      transition: 0.2s;
      outline: none;
    }

    .input-group input:focus {
      border-color: #2c7da0;
      box-shadow: 0 0 0 3px rgba(44,125,160,0.2);
    }

    button {
      background: #2c7da0;
      color: white;
      border: none;
      padding: 0.75rem 1.6rem;
      border-radius: 40px;
      font-weight: bold;
      font-size: 0.9rem;
      cursor: pointer;
      transition: 0.2s;
      box-shadow: 0 2px 5px rgba(0,0,0,0.1);
      margin-top: 0.5rem;
      margin-right: 0.8rem;
    }

    button:hover {
      background: #1f617e;
      transform: translateY(-2px);
    }

    .btn-secondary {
      background: #3b7b5e;
    }
    .btn-secondary:hover {
      background: #2b5e47;
    }

    .btn-warning {
      background: #b5651e;
    }
    .btn-warning:hover {
      background: #9a4f15;
    }

    .btn-outline {
      background: transparent;
      border: 2px solid #2c7da0;
      color: #2c7da0;
    }
    .btn-outline:hover {
      background: #e3f0f5;
      transform: translateY(-1px);
    }

    .stock-table-wrapper {
      overflow-x: auto;
      border-radius: 24px;
    }

    table {
      width: 100%;
      border-collapse: collapse;
      background: white;
      border-radius: 24px;
      overflow: hidden;
    }

    th {
      background: #1e3b4a;
      color: white;
      padding: 14px 12px;
      font-weight: 600;
      text-align: left;
    }

    td {
      padding: 12px 12px;
      border-bottom: 1px solid #e2e8f0;
      color: #1e2f3c;
      font-weight: 500;
    }

    tr:hover td {
      background-color: #f8fcff;
    }

    .price-positive {
      color: #2b7a4b;
      font-weight: 700;
    }

    .empty-row td {
      text-align: center;
      padding: 2rem;
      color: #7f8c8d;
      font-style: italic;
    }

    .update-form-inline {
      background: #fef9e6;
      padding: 0.8rem;
      border-radius: 28px;
      margin-top: 0.8rem;
      display: flex;
      flex-wrap: wrap;
      gap: 0.6rem;
      align-items: flex-end;
    }

    .update-form-inline .input-group {
      margin-bottom: 0;
      flex: 1;
    }

    .update-form-inline input {
      padding: 0.5rem 0.8rem;
    }

    .message-bar {
      position: fixed;
      bottom: 20px;
      right: 20px;
      background: #1e2f3c;
      color: white;
      padding: 12px 20px;
      border-radius: 60px;
      font-size: 0.9rem;
      z-index: 1000;
      box-shadow: 0 5px 15px rgba(0,0,0,0.2);
      transition: opacity 0.3s;
      pointer-events: none;
    }

    @media (max-width: 750px) {
      body {
        padding: 1rem;
      }
      .card {
        padding: 1.2rem;
      }
      th, td {
        padding: 8px 6px;
        font-size: 0.8rem;
      }
      button {
        padding: 0.6rem 1.2rem;
      }
    }
  </style>
</head>
<body>
<div class="app-container">
  <div class="header">
    <h1>📈 Stock Price Management System</h1>
    <p>Array · Structure (Object) · Modular Functions | Add, Update, Display & Search</p>
  </div>

  <!-- Add Stock + Search Section (two panels) -->
  <div class="card">
    <h2>📊 Stock Operations</h2>
    <div class="grid-2col">
      <!-- ADD STOCK SECTION -->
      <div class="form-panel">
        <h3 style="margin-bottom: 1rem; font-size: 1.3rem;">➕ Add New Stock</h3>
        <div class="input-group">
          <label>🏢 Company Name</label>
          <input type="text" id="companyName" placeholder="e.g., Tesla Inc." autocomplete="off">
        </div>
        <div class="input-group">
          <label>💵 Stock Price (USD)</label>
          <input type="number" id="stockPrice" step="0.01" placeholder="e.g., 245.75">
        </div>
        <div class="input-group">
          <label>📊 Symbol (optional)</label>
          <input type="text" id="stockSymbol" placeholder="e.g., TSLA">
        </div>
        <button id="addStockBtn">➕ Add Stock</button>
        <button id="resetDemoBtn" class="btn-outline" style="margin-left: 0.5rem;">⟳ Reset Demo Data</button>
      </div>

      <!-- SEARCH BY COMPANY NAME -->
      <div class="search-panel">
        <h3 style="margin-bottom: 1rem; font-size: 1.3rem;">🔍 Search Stock</h3>
        <div class="input-group">
          <label>Company Name (partial or full)</label>
          <input type="text" id="searchInput" placeholder="Type company name... e.g., Apple" autocomplete="off">
        </div>
        <button id="searchBtn">🔎 Search</button>
        <button id="resetSearchBtn" class="btn-outline">Show All Stocks</button>
        <div id="searchFeedback" style="margin-top: 0.8rem; font-size: 0.85rem; color: #2c7da0;"></div>
      </div>
    </div>
  </div>

  <!-- Display all stocks + update price section embedded -->
  <div class="card">
    <h2>📋 All Stocks & Price Management</h2>
    <div class="stock-table-wrapper">
      <table id="stockTable">
        <thead>
          <tr><th>ID</th><th>Company Name</th><th>Symbol</th><th>Current Price (USD)</th><th>Actions</th></tr>
        </thead>
        <tbody id="stockTableBody">
          <tr class="empty-row"><td colspan="5">No stocks available. Add some stocks.</td></tr>
        </tbody>
      </table>
    </div>
    <div style="margin-top: 1.2rem; display: flex; justify-content: flex-end;">
      <button id="refreshDisplayBtn" class="btn-secondary">🔄 Refresh Display</button>
    </div>
  </div>
</div>

<div id="messageToast" class="message-bar" style="opacity:0; visibility:hidden;">✅ Message</div>

<script>
  // ---------- STRUCTURE (using JavaScript Object) ----------
  // Each stock is an object: { id, companyName, symbol, price }
  // We use an ARRAY to store all stocks.
  let stocksArray = [];

  // Helper: generate next ID (simple incremental)
  let nextId = 1;

  // ---------- UTILITY FUNCTIONS (Core Functions) ----------
  // Function to display a temporary toast message
  function showMessage(msg, isError = false) {
    const toast = document.getElementById('messageToast');
    toast.textContent = msg;
    toast.style.backgroundColor = isError ? '#b13e3e' : '#1e2f3c';
    toast.style.opacity = '1';
    toast.style.visibility = 'visible';
    setTimeout(() => {
      toast.style.opacity = '0';
      toast.style.visibility = 'hidden';
      toast.style.backgroundColor = '#1e2f3c';
    }, 2800);
  }

  // 1. Add stock details (Structure + Array push)
  function addStock(companyName, symbol, price) {
    // validation: company name required, price must be valid number >0
    if (!companyName || companyName.trim() === "") {
      showMessage("❌ Company name cannot be empty!", true);
      return false;
    }
    const priceNum = parseFloat(price);
    if (isNaN(priceNum) || priceNum <= 0) {
      showMessage("❌ Please enter a valid positive stock price.", true);
      return false;
    }
    // optional symbol: if empty set to 'N/A'
    const finalSymbol = (symbol && symbol.trim() !== "") ? symbol.trim().toUpperCase() : "—";
    const newStock = {
      id: nextId++,
      companyName: companyName.trim(),
      symbol: finalSymbol,
      price: priceNum
    };
    stocksArray.push(newStock);
    showMessage(`✅ Stock "${newStock.companyName}" added with price $${newStock.price.toFixed(2)}`);
    return true;
  }

  // 2. Update stock price by stock id (function updateStockPrice)
  function updateStockPrice(stockId, newPrice) {
    const priceNum = parseFloat(newPrice);
    if (isNaN(priceNum) || priceNum <= 0) {
      showMessage("❌ Update failed: Price must be a positive number.", true);
      return false;
    }
    const stock = stocksArray.find(s => s.id === stockId);
    if (!stock) {
      showMessage("❌ Stock not found! Cannot update.", true);
      return false;
    }
    const oldPrice = stock.price;
    stock.price = priceNum;
    showMessage(`💰 Updated "${stock.companyName}" price: $${oldPrice.toFixed(2)} → $${priceNum.toFixed(2)}`);
    return true;
  }

  // 3. Display all stocks (render table)
  function displayAllStocks() {
    renderStockTable(stocksArray);
  }

  // 4. Search stock by company name (case-insensitive, partial match)
  function searchStockByCompanyName(searchTerm) {
    if (!searchTerm || searchTerm.trim() === "") {
      showMessage("🔍 Please enter a company name to search.", true);
      return [];
    }
    const term = searchTerm.trim().toLowerCase();
    const filtered = stocksArray.filter(stock => 
      stock.companyName.toLowerCase().includes(term)
    );
    if (filtered.length === 0) {
      showMessage(`🔎 No stocks found matching "${searchTerm}"`, true);
    } else {
      showMessage(`📌 Found ${filtered.length} stock(s) matching "${searchTerm}"`);
    }
    return filtered;
  }

  // Helper render function: accepts array of stocks (structure)
  function renderStockTable(stocksToRender) {
    const tbody = document.getElementById('stockTableBody');
    if (!tbody) return;
    if (!stocksToRender || stocksToRender.length === 0) {
      tbody.innerHTML = `<tr class="empty-row"><td colspan="5">📭 No stocks available. Add new stocks using the form.</td></tr>`;
      return;
    }
    tbody.innerHTML = "";
    for (let i = 0; i < stocksToRender.length; i++) {
      const stock = stocksToRender[i];
      const row = tbody.insertRow();
      // ID cell
      const cellId = row.insertCell(0);
      cellId.textContent = stock.id;
      // Company name
      const cellName = row.insertCell(1);
      cellName.textContent = stock.companyName;
      // Symbol
      const cellSym = row.insertCell(2);
      cellSym.textContent = stock.symbol;
      // Price
      const cellPrice = row.insertCell(3);
      cellPrice.innerHTML = `<span class="price-positive">$${stock.price.toFixed(2)}</span>`;
      // Actions: update button + inline mini form
      const cellAction = row.insertCell(4);
      // Create container for update controls
      const updateContainer = document.createElement('div');
      updateContainer.style.display = 'flex';
      updateContainer.style.flexWrap = 'wrap';
      updateContainer.style.gap = '8px';
      updateContainer.style.alignItems = 'center';

      // input field for new price
      const priceInput = document.createElement('input');
      priceInput.type = 'number';
      priceInput.step = '0.01';
      priceInput.placeholder = 'New price';
      priceInput.style.padding = '6px 10px';
      priceInput.style.borderRadius = '30px';
      priceInput.style.border = '1px solid #ccc';
      priceInput.style.width = '110px';
      
      const updateBtn = document.createElement('button');
      updateBtn.textContent = 'Update';
      updateBtn.style.background = '#3b7b5e';
      updateBtn.style.padding = '6px 14px';
      updateBtn.style.margin = '0';
      updateBtn.style.fontSize = '0.8rem';
      
      updateBtn.addEventListener('click', (function(stockId) {
        return function() {
          const newPriceVal = priceInput.value;
          if (newPriceVal === "") {
            showMessage("⚠️ Enter a new price before updating.", true);
            return;
          }
          const success = updateStockPrice(stockId, newPriceVal);
          if (success) {
            // re-render full current view (but keep search state? we call display based on current active mode)
            // After update, we refresh the display according to current active filter (if any)
            refreshCurrentView();
            priceInput.value = ""; // clear local input
          }
        };
      })(stock.id));
      
      updateContainer.appendChild(priceInput);
      updateContainer.appendChild(updateBtn);
      cellAction.appendChild(updateContainer);
    }
  }

  // Global state for search filter: null means show all stocks, else filtered array reference or search term
  let activeFilteredStocks = null;       // if not null, store array that is currently displayed
  let lastSearchTerm = "";

  // refresh current view based on activeFilter: if activeFilteredStocks exists, render that, else render full array
  function refreshCurrentView() {
    if (activeFilteredStocks !== null && lastSearchTerm !== "") {
      // re-apply search because the array might have changed (like update/delete/add), we re-filter based on lastSearchTerm
      const newFiltered = stocksArray.filter(stock => 
        stock.companyName.toLowerCase().includes(lastSearchTerm.toLowerCase())
      );
      activeFilteredStocks = newFiltered;
      renderStockTable(activeFilteredStocks);
      const feedbackDiv = document.getElementById('searchFeedback');
      if(feedbackDiv) feedbackDiv.innerHTML = `🔍 Showing results for: "${lastSearchTerm}" (${newFiltered.length} stocks)`;
    } else {
      activeFilteredStocks = null;
      lastSearchTerm = "";
      renderStockTable(stocksArray);
      const feedbackDiv = document.getElementById('searchFeedback');
      if(feedbackDiv) feedbackDiv.innerHTML = "";
    }
  }

  // Function to perform search and update UI
  function performSearch() {
    const searchInput = document.getElementById('searchInput');
    const term = searchInput.value;
    if (!term.trim()) {
      // if empty search: reset to all stocks
      resetSearchAndDisplay();
      showMessage("📋 Displaying all stocks");
      return;
    }
    const results = searchStockByCompanyName(term);
    // update state
    activeFilteredStocks = results;
    lastSearchTerm = term.trim();
    renderStockTable(results);
    const feedbackDiv = document.getElementById('searchFeedback');
    if (feedbackDiv) {
      if(results.length === 0) feedbackDiv.innerHTML = `❌ No company matches "${term}"`;
      else feedbackDiv.innerHTML = `✅ ${results.length} stock(s) found for "${term}"`;
    }
  }

  function resetSearchAndDisplay() {
    document.getElementById('searchInput').value = "";
    activeFilteredStocks = null;
    lastSearchTerm = "";
    renderStockTable(stocksArray);
    const feedbackDiv = document.getElementById('searchFeedback');
    if(feedbackDiv) feedbackDiv.innerHTML = "";
    showMessage("📋 Showing all stocks");
  }

  // add new stock from UI, then refresh current view (preserving search if active)
  function handleAddStock() {
    const company = document.getElementById('companyName').value;
    const price = document.getElementById('stockPrice').value;
    const symbol = document.getElementById('stockSymbol').value;
    const success = addStock(company, symbol, price);
    if (success) {
      // clear only company & price & symbol but keep convenience?
      document.getElementById('companyName').value = "";
      document.getElementById('stockPrice').value = "";
      document.getElementById('stockSymbol').value = "";
      // After addition, refresh the current view (search mode or all)
      refreshCurrentView();
      // focus on company field
      document.getElementById('companyName').focus();
    }
  }

  // reset demo data: populate with some cool default stocks using the structure concept
  function resetDemoData() {
    // create fresh array, reset nextId
    stocksArray = [];
    nextId = 1;
    // demo stocks: (Array of stock objects)
    const demoStocks = [
      { companyName: "Apple Inc.", symbol: "AAPL", price: 175.34 },
      { companyName: "Microsoft Corporation", symbol: "MSFT", price: 332.50 },
      { companyName: "Tesla, Inc.", symbol: "TSLA", price: 245.75 },
      { companyName: "Amazon.com Inc.", symbol: "AMZN", price: 128.20 },
      { companyName: "Google (Alphabet)", symbol: "GOOGL", price: 138.92 }
    ];
    for (const demo of demoStocks) {
      stocksArray.push({
        id: nextId++,
        companyName: demo.companyName,
        symbol: demo.symbol,
        price: demo.price
      });
    }
    // reset search filters & update ui
    resetSearchAndDisplay();
    showMessage("✨ Demo stocks loaded (Apple, Microsoft, Tesla, Amazon, Google)");
    // clear any active filter
    activeFilteredStocks = null;
    lastSearchTerm = "";
    document.getElementById('searchInput').value = "";
    const feedbackDiv = document.getElementById('searchFeedback');
    if(feedbackDiv) feedbackDiv.innerHTML = "";
  }

  // manual refresh button: re-render with current filter state (just in case)
  function manualRefresh() {
    refreshCurrentView();
    showMessage("🔄 Stock list refreshed");
  }

  // Event listeners & initialization
  document.addEventListener('DOMContentLoaded', () => {
    // Load demo data initially so UI is not empty (concepts showcase)
    resetDemoData();

    // bind buttons
    const addBtn = document.getElementById('addStockBtn');
    if (addBtn) addBtn.addEventListener('click', handleAddStock);
    
    const resetDemoBtn = document.getElementById('resetDemoBtn');
    if (resetDemoBtn) resetDemoBtn.addEventListener('click', resetDemoData);
    
    const searchBtn = document.getElementById('searchBtn');
    if (searchBtn) searchBtn.addEventListener('click', performSearch);
    
    const resetSearch = document.getElementById('resetSearchBtn');
    if (resetSearch) resetSearch.addEventListener('click', () => {
      resetSearchAndDisplay();
      document.getElementById('searchInput').value = "";
    });
    
    const refreshBtn = document.getElementById('refreshDisplayBtn');
    if (refreshBtn) refreshBtn.addEventListener('click', manualRefresh);
    
    // Additional: allow pressing Enter in search input
    const searchInputField = document.getElementById('searchInput');
    if (searchInputField) {
      searchInputField.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') performSearch();
      });
    }
    // allow enter on add fields? optional: add stock price/company
    const companyField = document.getElementById('companyName');
    const priceField = document.getElementById('stockPrice');
    const addStockFromEnter = () => { handleAddStock(); };
    if (companyField) companyField.addEventListener('keypress', (e) => { if(e.key === 'Enter') addStockFromEnter(); });
    if (priceField) priceField.addEventListener('keypress', (e) => { if(e.key === 'Enter') addStockFromEnter(); });
  });

  // Expose for console debugging (optional to demonstrate structure)
  window.stockSystem = {
    getStocks: () => [...stocksArray],
    addStock,
    updateStockPrice,
    searchStockByCompanyName,
    displayAllStocks: () => renderStockTable(stocksArray)
  };
</script>
</body>
</html>
