const header = document.querySelector(".site-header");
const navToggle = document.querySelector(".nav-toggle");
const navLinks = document.querySelector(".nav-links");
const navItems = document.querySelectorAll('.nav-links a[href^="#"]');
const year = document.querySelector("#current-year");
const sections = document.querySelectorAll(".section");
const revealItems = document.querySelectorAll(
  ".experience-card, .project-card, .academic-year, .skill-group, .credential-list article, .achievement-list article, .about-education, .callout-card"
);
const heroItems = document.querySelectorAll(
  ".hero .eyebrow, .hero h1, .hero-title, .hero-intro, .hero-actions, .hero-highlights, .portrait-wrap"
);
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

if (!prefersReducedMotion && "IntersectionObserver" in window) {
  heroItems.forEach((item, index) => {
    item.classList.add("hero-reveal");
    item.style.setProperty("--reveal-delay", `${90 + index * 90}ms`);
  });

  sections.forEach((section) => section.classList.add("reveal"));
  revealItems.forEach((item, index) => {
    item.classList.add("reveal-item");
    item.style.setProperty("--reveal-delay", `${(index % 4) * 80}ms`);
  });

  requestAnimationFrame(() => {
    requestAnimationFrame(() => {
      document.querySelector(".hero")?.classList.add("is-visible");
      window.setTimeout(() => {
        heroItems.forEach((item) => item.style.removeProperty("--reveal-delay"));
      }, 1500);
    });
  });

  const revealLinkedSection = () => {
    if (window.location.hash) {
      document.querySelector(window.location.hash)?.classList.add("is-visible");
    }
  };

  revealLinkedSection();
  window.addEventListener("load", revealLinkedSection);

  const sectionObserver = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          entry.target.classList.add("is-visible");
          window.setTimeout(
            () => entry.target.style.removeProperty("--reveal-delay"),
            1200
          );
        } else {
          entry.target.classList.remove("is-visible");
        }
      });
    },
    {
      threshold: 0.05,
      rootMargin: window.innerWidth > 900
        ? "-8% 0px -16% 0px"
        : "-5% 0px -10% 0px",
    }
  );

  sections.forEach((section) => sectionObserver.observe(section));

  const itemObserver = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          entry.target.classList.add("is-visible");
          window.setTimeout(
            () => entry.target.style.removeProperty("--reveal-delay"),
            1200
          );
        } else {
          entry.target.classList.remove("is-visible");
        }
      });
    },
    {
      threshold: 0.08,
      rootMargin: window.innerWidth > 900
        ? "-5% 0px -12% 0px"
        : "-3% 0px -8% 0px",
    }
  );

  revealItems.forEach((item) => itemObserver.observe(item));
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
