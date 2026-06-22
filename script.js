const header = document.querySelector(".site-header");
const navToggle = document.querySelector(".nav-toggle");
const navLinks = document.querySelector(".nav-links");
const navItems = document.querySelectorAll('.nav-links a[href^="#"]');
const year = document.querySelector("#current-year");
const sections = document.querySelectorAll(".section");
const prefersReducedMotion = window.matchMedia("(prefers-reduced-motion: reduce)").matches;

if (year) {
  year.textContent = new Date().getFullYear();
}

const updateHeader = () => {
  header?.classList.toggle("scrolled", window.scrollY > 20);
};

updateHeader();
window.addEventListener("scroll", updateHeader, { passive: true });

const trackedSections = Array.from(navItems)
  .map((link) => document.querySelector(link.getAttribute("href")))
  .filter(Boolean);

const setActiveNav = (sectionId) => {
  navItems.forEach((link) => {
    const isActive = link.getAttribute("href") === `#${sectionId}`;
    link.classList.toggle("active", isActive);

    if (isActive) {
      link.setAttribute("aria-current", "location");
    } else {
      link.removeAttribute("aria-current");
    }
  });
};

if ("IntersectionObserver" in window && trackedSections.length) {
  const visibleSections = new Map();

  const navObserver = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          visibleSections.set(entry.target.id, entry.intersectionRatio);
        } else {
          visibleSections.delete(entry.target.id);
        }
      });

      const activeSection = [...visibleSections.entries()].sort(
        (a, b) => b[1] - a[1]
      )[0];

      if (activeSection) {
        setActiveNav(activeSection[0]);
      }
    },
    {
      rootMargin: "-20% 0px -55% 0px",
      threshold: [0.01, 0.2, 0.5, 0.8],
    }
  );

  trackedSections.forEach((section) => navObserver.observe(section));
}

const showElement = (element) => {
  element.classList.add("is-visible");
};

if (!prefersReducedMotion) {
  const hero = document.querySelector(".hero");
  const heroSequence = [
    [".hero .eyebrow", 140],
    [".hero h1", 300],
    [".portrait-wrap", 440],
    [".hero-title", 540],
    [".hero-intro", 700],
    [".hero-actions", 880],
    [".hero-highlights", 1060],
  ];

  heroSequence.forEach(([selector, delay]) => {
    const item = document.querySelector(selector);

    if (item) {
      item.classList.add("hero-reveal");
      item.style.setProperty("--reveal-delay", `${delay}ms`);
    }
  });

  sections.forEach((section) => section.classList.add("reveal-section"));

  const revealGroups = [
    ".about-education",
    ".experience-list .experience-card",
    ".project-grid .project-card",
    ".academic-grid .academic-year",
    ".skills-grid .skill-group",
    ".credential-list article",
    ".achievement-list article",
    ".contact-links a",
  ];
  const revealItems = [];

  revealGroups.forEach((selector) => {
    document.querySelectorAll(selector).forEach((item, index) => {
      item.classList.add("reveal-item");
      item.style.setProperty("--reveal-delay", `${(index % 4) * 120}ms`);
      revealItems.push(item);
    });
  });

  requestAnimationFrame(() => {
    requestAnimationFrame(() => hero?.classList.add("is-visible"));
  });

  if ("IntersectionObserver" in window) {
    const sectionObserver = new IntersectionObserver(
      (entries, observer) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            showElement(entry.target);
            observer.unobserve(entry.target);
          }
        });
      },
      {
        threshold: 0.12,
        rootMargin: "0px 0px -10% 0px",
      }
    );

    const itemObserver = new IntersectionObserver(
      (entries, observer) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            showElement(entry.target);
            observer.unobserve(entry.target);
          }
        });
      },
      {
        threshold: 0.1,
        rootMargin: "0px 0px -6% 0px",
      }
    );

    const revealLinkedSection = () => {
      if (!window.location.hash) return;

      const linkedSection = document.querySelector(window.location.hash);

      if (linkedSection) {
        showElement(linkedSection);
        linkedSection.querySelectorAll(".reveal-item").forEach(showElement);
      }
    };

    revealLinkedSection();
    window.addEventListener("hashchange", revealLinkedSection);

    window.setTimeout(() => {
      sections.forEach((section) => sectionObserver.observe(section));
      revealItems.forEach((item) => itemObserver.observe(item));
    }, 900);
  } else {
    sections.forEach(showElement);
    revealItems.forEach(showElement);
  }
}

if (navToggle && navLinks) {
  const closeMenu = () => {
    navToggle.setAttribute("aria-expanded", "false");
    navLinks.classList.remove("open");
    document.body.classList.remove("menu-open");
  };

  navToggle.addEventListener("click", () => {
    const isOpen = navToggle.getAttribute("aria-expanded") === "true";
    navToggle.setAttribute("aria-expanded", String(!isOpen));
    navLinks.classList.toggle("open", !isOpen);
    document.body.classList.toggle("menu-open", !isOpen);
  });

  navLinks.querySelectorAll("a").forEach((link) => {
    link.addEventListener("click", closeMenu);
  });

  window.addEventListener("resize", () => {
    if (window.innerWidth > 768) {
      closeMenu();
    }
  });
}
