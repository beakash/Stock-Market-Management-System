// ==================== MAIN APPLICATION ====================
import { fetchStockPrice, saveApiKey, useDemoMode, getApiKeyStatus } from './api.js';

// State
let stocksArray = [];
let nextId = 1;
let activeFilteredStocks = null;
let lastSearchTerm = "";

// DOM References
const elements = {
  companyName: document.getElementById('companyName'),
  stockPrice: document.getElementById('stockPrice'),
  stockSymbol: document.getElementById('stockSymbol'),
  searchInput: document.getElementById('searchInput'),
  liveSymbolInput: document.getElementById('liveSymbolInput'),
  stockSelectForUpdate: document.getElementById('stockSelectForUpdate'),
  stockTableBody: document.getElementById('stockTableBody'),
  searchFeedback: document.getElementById('searchFeedback'),
  liveQuoteDisplay: document.getElementById('liveQuoteDisplay'),
  apiKeyStatus: document.getElementById('apiKeyStatus'),
  apiStatus: document.getElementById('apiStatus'),
  messageToast: document.getElementById('messageToast'),
  alphaVantageApiKey: document.getElementById('alphaVantageApiKey')
};

// ==================== UI HELPERS ====================
function showMessage(msg, isError = false) {
  const toast = elements.messageToast;
  if (!toast) return;
  toast.textContent = msg;
  toast.style.backgroundColor = isError ? '#e11d48' : '#0f172a';
  toast.classList.add('visible');
  clearTimeout(toast._timeout);
  toast._timeout = setTimeout(() => {
    toast.classList.remove('visible');
  }, 3200);
}

// ==================== STOCK MANAGEMENT ====================
function addStock(companyName, symbol, price) {
  if (!companyName || companyName.trim() === "") {
    showMessage("❌ Company name required", true);
    return false;
  }
  const priceNum = parseFloat(price);
  if (isNaN(priceNum) || priceNum <= 0) {
    showMessage("❌ Please enter a valid positive stock price", true);
    return false;
  }
  const finalSymbol = (symbol && symbol.trim() !== "") ? symbol.trim().toUpperCase() : "—";
  const newStock = {
    id: nextId++,
    companyName: companyName.trim(),
    symbol: finalSymbol,
    price: priceNum
  };
  stocksArray.push(newStock);
  showMessage(`✅ Stock "${newStock.companyName}" added at $${newStock.price.toFixed(2)}`);
  return true;
}

function updateStockPrice(stockId, newPrice) {
  const priceNum = parseFloat(newPrice);
  if (isNaN(priceNum) || priceNum <= 0) {
    showMessage("❌ Price must be a positive number", true);
    return false;
  }
  const stock = stocksArray.find(s => s.id === stockId);
  if (!stock) {
    showMessage("❌ Stock not found", true);
    return false;
  }
  const oldPrice = stock.price;
  stock.price = priceNum;
  showMessage(`💰 Updated "${stock.companyName}": $${oldPrice.toFixed(2)} → $${priceNum.toFixed(2)}`);
  return true;
}

function deleteStock(stockId) {
  const stockIndex = stocksArray.findIndex(s => s.id === stockId);
  if (stockIndex !== -1) {
    const deleted = stocksArray.splice(stockIndex, 1)[0];
    showMessage(`🗑️ Deleted "${deleted.companyName}" from portfolio`);
    refreshCurrentView();
    return true;
  }
  return false;
}

function searchStockByCompanyName(searchTerm) {
  if (!searchTerm || searchTerm.trim() === "") return [];
  const term = searchTerm.trim().toLowerCase();
  return stocksArray.filter(stock => 
    stock.companyName.toLowerCase().includes(term) ||
    stock.symbol.toLowerCase().includes(term)
  );
}

// ==================== RENDER FUNCTIONS ====================
function renderStockTable(stocksToRender) {
  const tbody = elements.stockTableBody;
  if (!tbody) return;
  
  if (!stocksToRender || stocksToRender.length === 0) {
    tbody.innerHTML = '<tr class="empty-row"><td colspan="5">📭 No stocks available in portfolio. Add some stocks above.</td></tr>';
    return;
  }
  
  tbody.innerHTML = "";
  for (const stock of stocksToRender) {
    const row = tbody.insertRow();
    
    // ID
    const cellId = row.insertCell(0);
    cellId.textContent = `#${stock.id}`;
    cellId.style.fontWeight = "600";
    cellId.style.color = "#64748b";

    // Company Name
    const cellName = row.insertCell(1);
    cellName.textContent = stock.companyName;
    cellName.style.fontWeight = "600";

    // Ticker Symbol
    const cellSymbol = row.insertCell(2);
    cellSymbol.innerHTML = `<span class="symbol-badge">${stock.symbol}</span>`;

    // Price
    const cellPrice = row.insertCell(3);
    cellPrice.innerHTML = `<span class="price-display">$${stock.price.toFixed(2)}</span>`;
    
    // Action Cell
    const actionCell = row.insertCell(4);
    const container = document.createElement('div');
    container.style.display = 'flex';
    container.style.gap = '6px';
    container.style.alignItems = 'center';
    container.style.flexWrap = 'wrap';
    
    const priceInput = document.createElement('input');
    priceInput.type = 'number';
    priceInput.step = '0.01';
    priceInput.placeholder = 'New price';
    priceInput.style.padding = '5px 8px';
    priceInput.style.borderRadius = '6px';
    priceInput.style.border = '1px solid #cbd5e1';
    priceInput.style.fontSize = '0.85rem';
    priceInput.style.width = '95px';
    
    const updateBtn = document.createElement('button');
    updateBtn.textContent = 'Update';
    updateBtn.className = 'btn-secondary btn-small';
    
    updateBtn.onclick = (function(id) {
      return function() {
        const newPrice = priceInput.value;
        if (!newPrice) {
          showMessage("Please enter a price", true);
          return;
        }
        if (updateStockPrice(id, newPrice)) {
          refreshCurrentView();
          updateStockSelectDropdown();
          priceInput.value = '';
        }
      };
    })(stock.id);

    const deleteBtn = document.createElement('button');
    deleteBtn.textContent = '✕';
    deleteBtn.className = 'btn-danger btn-small';
    deleteBtn.title = 'Delete Stock';
    deleteBtn.onclick = (function(id) {
      return function() {
        deleteStock(id);
      };
    })(stock.id);
    
    container.appendChild(priceInput);
    container.appendChild(updateBtn);
    container.appendChild(deleteBtn);
    actionCell.appendChild(container);
  }
}

function refreshCurrentView() {
  if (activeFilteredStocks !== null && lastSearchTerm !== "") {
    const newFiltered = stocksArray.filter(s => 
      s.companyName.toLowerCase().includes(lastSearchTerm.toLowerCase()) ||
      s.symbol.toLowerCase().includes(lastSearchTerm.toLowerCase())
    );
    activeFilteredStocks = newFiltered;
    renderStockTable(activeFilteredStocks);
    if (elements.searchFeedback) {
      elements.searchFeedback.innerHTML = `🔍 Showing results for "${lastSearchTerm}" (${newFiltered.length} stocks)`;
    }
  } else {
    activeFilteredStocks = null;
    lastSearchTerm = "";
    renderStockTable(stocksArray);
    if (elements.searchFeedback) {
      elements.searchFeedback.innerHTML = "";
    }
  }
  updateStockSelectDropdown();
}

function resetSearchAndDisplay() {
  elements.searchInput.value = "";
  activeFilteredStocks = null;
  lastSearchTerm = "";
  renderStockTable(stocksArray);
  if (elements.searchFeedback) {
    elements.searchFeedback.innerHTML = "";
  }
  showMessage("📋 Showing all stocks");
}

function performSearch() {
  const term = elements.searchInput.value;
  if (!term.trim()) {
    resetSearchAndDisplay();
    return;
  }
  const results = searchStockByCompanyName(term);
  activeFilteredStocks = results;
  lastSearchTerm = term.trim();
  renderStockTable(results);
  const fb = elements.searchFeedback;
  fb.innerHTML = results.length ? `✅ Found ${results.length} stock(s) matching "${term}"` : `❌ No stocks match "${term}"`;
}

function updateStockSelectDropdown() {
  const selectEl = elements.stockSelectForUpdate;
  if (!selectEl) return;
  selectEl.innerHTML = '<option value="">-- Choose Stock --</option>';
  stocksArray.forEach(stock => {
    const option = document.createElement('option');
    option.value = stock.id;
    option.textContent = `${stock.companyName} (${stock.symbol}) - $${stock.price.toFixed(2)}`;
    selectEl.appendChild(option);
  });
}

// ==================== API INTEGRATION ====================
async function handleFetchLivePrice() {
  const symbol = elements.liveSymbolInput.value.trim();
  if (!symbol) {
    showMessage("Please enter a stock symbol (e.g., AAPL, TSLA, NVDA)", true);
    return;
  }
  
  const displaySpan = elements.liveQuoteDisplay;
  displaySpan.innerHTML = '<span class="spinner-small"></span> Fetching market quote...';
  
  try {
    const price = await fetchStockPrice(symbol);
    displaySpan.innerHTML = `💰 $${price.toFixed(2)} (${symbol.toUpperCase()}) <span style="font-size:0.75rem; color:#059669;">✓ Live Sync</span>`;
    showMessage(`Live price for ${symbol.toUpperCase()}: $${price.toFixed(2)}`);
    elements.liveSymbolInput.setAttribute('data-last-price', price);
  } catch (error) {
    displaySpan.innerHTML = `⚠️ Could not fetch: ${error.message}`;
    showMessage(`Failed to fetch price for ${symbol}`, true);
  }
}

async function handleUpdateSelectedStock() {
  const selectedId = elements.stockSelectForUpdate.value;
  if (!selectedId) {
    showMessage("Please select a stock from the dropdown", true);
    return;
  }
  
  const symbolInput = elements.liveSymbolInput.value.trim();
  if (!symbolInput) {
    showMessage("Please enter a stock symbol in the Live Ticker field", true);
    return;
  }
  
  const symbolToFetch = symbolInput.toUpperCase();
  const stock = stocksArray.find(s => s.id == selectedId);
  if (!stock) {
    showMessage("Stock not found", true);
    return;
  }
  
  const updateBtn = document.getElementById('updateSelectedStockBtn');
  const originalText = updateBtn.textContent;
  updateBtn.innerHTML = '<span class="spinner-small"></span> Updating...';
  updateBtn.disabled = true;
  
  try {
    const livePrice = await fetchStockPrice(symbolToFetch);
    stock.price = livePrice;
    if (stock.symbol === "—" || stock.symbol !== symbolToFetch) {
      stock.symbol = symbolToFetch;
    }
    showMessage(`✅ ${stock.companyName} updated to $${livePrice.toFixed(2)} via API`);
    refreshCurrentView();
    updateStockSelectDropdown();
    elements.liveQuoteDisplay.innerHTML = `✅ Updated: $${livePrice.toFixed(2)}`;
  } catch (error) {
    showMessage(`API update failed: ${error.message}`, true);
  } finally {
    updateBtn.innerHTML = originalText;
    updateBtn.disabled = false;
  }
}

async function syncAllStocks() {
  if (stocksArray.length === 0) {
    showMessage("No stocks in portfolio to sync", true);
    return;
  }
  
  showMessage("🔄 Syncing portfolio with live market prices...");
  const syncBtn = document.getElementById('syncAllStocksBtn');
  const originalText = syncBtn.textContent;
  syncBtn.innerHTML = '<span class="spinner-small"></span> Syncing Portfolio...';
  syncBtn.disabled = true;
  
  let updatedCount = 0;
  let failedCount = 0;
  
  for (const stock of stocksArray) {
    if (stock.symbol && stock.symbol !== "—") {
      try {
        const livePrice = await fetchStockPrice(stock.symbol);
        stock.price = livePrice;
        updatedCount++;
        await new Promise(resolve => setTimeout(resolve, 300));
      } catch (error) {
        failedCount++;
        console.warn(`Failed to sync ${stock.symbol}: ${error.message}`);
      }
    }
  }
  
  refreshCurrentView();
  showMessage(`✅ Sync complete! ${updatedCount} stocks updated live.`);
  
  syncBtn.innerHTML = originalText;
  syncBtn.disabled = false;
}

// ==================== API KEY MANAGEMENT ====================
function handleSaveApiKey() {
  const keyInput = elements.alphaVantageApiKey.value.trim();
  if (keyInput === "") {
    showMessage("Please enter a valid API key or use demo", true);
    return;
  }
  try {
    saveApiKey(keyInput);
    elements.apiKeyStatus.innerHTML = '🔑 Custom API key active (Alpha Vantage + Yahoo)';
    showMessage(`API key saved successfully.`);
  } catch (error) {
    showMessage(error.message, true);
  }
}

function handleUseDemoKey() {
  useDemoMode();
  elements.alphaVantageApiKey.value = 'demo';
  elements.apiKeyStatus.innerHTML = '⚙️ Demo mode active (Yahoo Finance + Fallback simulation)';
  showMessage("Demo mode active: Yahoo Finance + Realistic Simulation");
}

// ==================== DEMO DATA ====================
function resetDemoData() {
  stocksArray = [];
  nextId = 1;
  
  const demoStocks = [
    { companyName: "Apple Inc.", symbol: "AAPL", price: 175.34 },
    { companyName: "Microsoft Corporation", symbol: "MSFT", price: 332.50 },
    { companyName: "Tesla, Inc.", symbol: "TSLA", price: 245.75 },
    { companyName: "Amazon.com Inc.", symbol: "AMZN", price: 128.20 },
    { companyName: "NVIDIA Corporation", symbol: "NVDA", price: 895.62 },
    { companyName: "Google (Alphabet)", symbol: "GOOGL", price: 138.92 },
    { companyName: "Meta Platforms", symbol: "META", price: 485.30 }
  ];
  
  for (const demo of demoStocks) {
    stocksArray.push({
      id: nextId++,
      companyName: demo.companyName,
      symbol: demo.symbol,
      price: demo.price
    });
  }
  
  resetSearchAndDisplay();
  updateStockSelectDropdown();
  showMessage("✨ Portfolio reloaded with top tech stocks!");
}

function manualRefresh() {
  refreshCurrentView();
  showMessage("🔄 Display refreshed");
}

// ==================== INITIALIZATION ====================
function loadSavedApiKey() {
  const status = getApiKeyStatus();
  if (status.hasKey) {
    elements.alphaVantageApiKey.value = status.key;
    elements.apiKeyStatus.innerHTML = '🔐 Custom Alpha Vantage key loaded';
  } else if (status.isDemo) {
    elements.alphaVantageApiKey.value = 'demo';
    elements.apiKeyStatus.innerHTML = '⚙️ Demo mode active (Yahoo + Fallback)';
  } else {
    elements.alphaVantageApiKey.value = '';
    elements.apiKeyStatus.innerHTML = '💡 Optional: Add Alpha Vantage key for high-rate live limits';
  }
}

// ==================== EVENT LISTENERS ====================
document.addEventListener('DOMContentLoaded', () => {
  loadSavedApiKey();
  resetDemoData();
  
  // Stock operations
  document.getElementById('addStockBtn').addEventListener('click', () => {
    const company = elements.companyName.value;
    const price = elements.stockPrice.value;
    const symbol = elements.stockSymbol.value;
    
    if (addStock(company, symbol, price)) {
      elements.companyName.value = "";
      elements.stockPrice.value = "";
      elements.stockSymbol.value = "";
      refreshCurrentView();
      elements.companyName.focus();
    }
  });
  
  document.getElementById('resetDemoBtn').addEventListener('click', resetDemoData);
  
  // Search
  document.getElementById('searchBtn').addEventListener('click', performSearch);
  document.getElementById('resetSearchBtn').addEventListener('click', () => {
    resetSearchAndDisplay();
    elements.searchInput.value = "";
  });
  
  // API
  document.getElementById('fetchLivePriceBtn').addEventListener('click', handleFetchLivePrice);
  document.getElementById('updateSelectedStockBtn').addEventListener('click', handleUpdateSelectedStock);
  document.getElementById('syncAllStocksBtn').addEventListener('click', syncAllStocks);
  document.getElementById('refreshDisplayBtn').addEventListener('click', manualRefresh);
  
  // API Key
  document.getElementById('saveApiKeyBtn').addEventListener('click', handleSaveApiKey);
  document.getElementById('useDemoKeyBtn').addEventListener('click', handleUseDemoKey);
  
  // Keyboard Enter handlers
  elements.searchInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') performSearch();
  });
  elements.companyName.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') document.getElementById('addStockBtn').click();
  });
  elements.liveSymbolInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') handleFetchLivePrice();
  });
});
